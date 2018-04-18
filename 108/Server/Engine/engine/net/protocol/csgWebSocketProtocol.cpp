#include "engine/net/protocol/csgWebSocketProtocol.h"
#include "framework/util/endian.h"
#include "../../rpc/rmidef.h"
#include "../../mq/msgBlock.h"
#include "../../rpc/rmiObjectAdapter.h"
#include "../../core/csgIoMgr.h"
#include "../session/sessionMgr.h"
#include "framework/3rd/websocket/websocketKeyHandler.h"
#include "framework/tool/memTool.h"
#include "framework/exception/exception.h"

int csg::CCsgWebSocketProtocol::handleRecvData(const CSessionPtr session,const void* inData, const int len)
{
	CAutoLock l(_readLock);

	if (!_is_complete_websocket_handshake) {
		//websocket 第一个包为握手包
		_websocket_handshake_data.append(inData, len);
		CWebSocketKeyHandlerPtr head_handler=new CWebSocketKeyHandler(_websocket_handshake_data);
		if (0 == head_handler->fetchHttpInfo()) {
			std::string res=head_handler->getRespondStr();
			handleSendData(session, res.c_str(),res.length());
			_is_complete_websocket_handshake = true;
			return 0;
		}
	}
	//decode websocket package
	int pos = 0;
	fetchFin((char*)inData, pos);
	fetchOpcode((char*)inData, pos);
	if (WS_CLOSING_FRAME == _opCode){
		LogInfo(__FUNCTION__ << " client reset session...,ip=" << session->getSocket()->remote_endpoint().address().to_string());
		return -1; //close socket
	}
	fetchMask((char*)inData, pos);
	fetchPayloadLength((char*)inData, pos);
	fetchMaskingKey((char*)inData, pos);
	fetchPayload((char*)inData, pos);

	if (_recvBuffer->getDataSize() + _payload_length > _maxRecvBuffSize) {
		LogErr(__FUNCTION__ << " recieve buffer size out of limit,now=" << (_recvBuffer->getDataSize() + len )<< ",limit=" << _maxRecvBuffSize);
		//超过缓冲区大小时直接断开连接
		return -1;
	}
	_recvBuffer->append(_payload, _payload_length);
	CCsgIoMgr::instance()->getLogicServer()->post(boost::bind(&CCsgWebSocketProtocol::handleReadData,this,session));
	return 0;
}

int csg::CCsgWebSocketProtocol::handleSendData(const CSessionPtr session, const void* data, const int len)
{
	if (len > 32767) {
		LogErr(__FUNCTION__ << " too many data,data.size=" << len);
		return -1;
	}
	uint8_t payloadFieldExtraBytes = (len <= 0x7d) ? 0 : 2;
	// header: 2字节, mask位设置为0(不加密), 则后面的masking key无须填写, 省略4字节  
	uint8_t frameHeaderSize = 2 + payloadFieldExtraBytes;
	uint8_t *frameHeader = new uint8_t[frameHeaderSize];
	memset(frameHeader, 0, frameHeaderSize);
	// fin位为1, 扩展位为0, 操作位为frameType  
	frameHeader[0] = static_cast<uint8_t>(0x80|WS_BINARY_FRAME);

	// 填充数据长度  
	if (len <= 0x7d)//125
	{
		frameHeader[1] = static_cast<uint8_t>(len);
	}
	else
	{
		frameHeader[1] = 0x7e;//126
		uint16_t len_ex = htons(len);
		memcpy(&frameHeader[2], &len_ex, payloadFieldExtraBytes);
	}

	// 填充数据  
	uint32_t frameSize = frameHeaderSize + len;
	char *frame = new char[frameSize + 1];
	memcpy(frame, frameHeader, frameHeaderSize);
	memcpy(frame + frameHeaderSize, data, len);
	frame[frameSize] = '\0';

	CAutoLock l(_writeLock);
	_sendBuffer->append(frame,frameHeaderSize+len);
	session->getSocket()->async_write_some(boost::asio::null_buffers(), boost::bind(&CCsgWebSocketProtocol::handleWriteDataEx,this, session, boost::asio::placeholders::error));
	return 0;
}

int csg::CCsgWebSocketProtocol::handleReadData(const CSessionPtr session)
{
	CAutoLock l(_readLock);
	do
	{
		if (_receiveHead)
		{
			if (_recvBuffer->getDataSize() < _protocolHead.msgSize)
			{
				//data not enough for a packet
				return 0;
			}
			else
			{
				//data enough for a packet
				try {
					if (-1 == handlePacket(session, _recvBuffer->getData() + SIZE_OF_PROTOCOL_HEAD, _protocolHead.msgSize))
					{
						LogInfo("CProtocol::handlePacket error,close the socket...");
// 						//解包错误时直接断开连接
// 						session->getSocket()->close();
// 						CSessionMgr::instance()->delSession(session);
						return -1;
					}
				}
				catch (csg::CException& ex) {
					LogErr(__FUNCTION__<<",csg ex="<<ex.what());
				}
				catch (std::exception& ex) {
					LogErr(__FUNCTION__ << ",std ex=" << ex.what());
				}
				catch (...) {
					LogErr(__FUNCTION__<<" unknow exception")
				}
				_recvBuffer->popData(_protocolHead.msgSize + SIZE_OF_PROTOCOL_HEAD);
				_receiveHead = false;
			}
		}
		else
		{
			if (_recvBuffer->getDataSize() >= SIZE_OF_PROTOCOL_HEAD)
			{
				memcpy(&_protocolHead, _recvBuffer->getData(), SIZE_OF_PROTOCOL_HEAD);
				_protocolHead.msgSize = endian(_protocolHead.msgSize);
				if (_protocolHead.msgSize > _maxRecvSize) {
					LogErr(__FUNCTION__<<" recieve package size out of limit,now="<<(int)_protocolHead.msgSize<<",limit="<<_maxRecvSize);
				}
				_receiveHead = true;
			}
			else
			{
				return 0;
			}
		}
	} while (true);

	return -1;
}

int csg::CCsgWebSocketProtocol::handleWriteData(const CSessionPtr session)
{

	return 0;
}

int csg::CCsgWebSocketProtocol::pushMessage(const CSessionPtr session,const CMsgBlockPtr& mb)
{
	CAutoSerializeStream  tmpOS(CSerializeStreamPool::instance()->newObject());

	_csg_write(*tmpOS, ERMIMessageTypeMQ);
	mb->_csg_write(*tmpOS);// _writeBody的时候写structType

	//整合发送前的flag数据
	tmpOS->prepareToAppend();

	CAutoSerializeStream  sendOs(CSerializeStreamPool::instance()->newObject());
	sendOs->writeSize(tmpOS->getFlagDataSize());
	sendOs->append(tmpOS->getFlagData(), tmpOS->getFlagDataSize());
	sendOs->append(tmpOS->getData(), tmpOS->getDataSize());

	//加协议头
	SProtocolHead head;
	head.msgSize = sendOs->getDataSize();
	CAutoSerializeStream addHeadOs(CSerializeStreamPool::instance()->newObject());
	addHeadOs->append(&head, SIZE_OF_PROTOCOL_HEAD);
	addHeadOs->append(sendOs->getData(), sendOs->getDataSize());

	return handleSendData(session, addHeadOs->getData(), addHeadOs->getDataSize());
}

int csg::CCsgWebSocketProtocol::handlePacket(const CSessionPtr session, const void *packageData, const int len)
{
	CAutoSerializeStream is(CSerializeStreamPool::instance()->newObject());
	is->append(packageData, len);

	is->setUseBitMark(false);

	is->prepareToRead();

	ERMIMessageType mqType;
	_csg_read(*is, mqType);

	switch (mqType)
	{
	case csg::ERMIMessageTypeMQ:
	{
		CMsgBlockPtr msg = new CMsgBlock();
		msg->_csg_read(*is);

		if (!msg)
		{
			assert(false);
			return -1;
		}
		msg->_msgBase->print();
	}
	break;
	case csg::ERMIMessageTypeCall:
	{
		SRMICall rmiCall;
		rmiCall._csg_read(*is);

		CRMIObjectPtr rmiOjbect;
		if (!CRMIObjectAdapter::instance()->findRmiObject(rmiCall.rpcId, rmiOjbect))
		{
			return -1;
		}
		is->setUseBitMark(true);
		rmiOjbect->__onCall(session, rmiCall, *is);
	}
	break;
	case csg::ERMIMessageTypeCallRet:
	{
		SRMIReturn rmiReturn;
		rmiReturn._csg_read(*is);

		is->setUseBitMark(true);

		LogInfo("CProtocol::handlePacket" << ",messageId=" << rmiReturn.messageId);

		if (rmiReturn.messageId <= 0)
			return 0;

		CRMIObjectBindPtr backObject;
		if (!session->getCallBackObject(rmiReturn.messageId, backObject))
		{
			return -1;
		}
		if (backObject->_callBack)
		{
			if (ERMIDispatchResultOk == rmiReturn.dispatchStatus) {
				backObject->_callBack->__response(*is);
			}
			else {
				backObject->_callBack->__exception(*is);
			}
		}
	}
	break;
	default:
	{
		LogErr("unkonw type=" << mqType);
		assert(false);
		return -1;
	}
	}

	return 0;
}

int csg::CCsgWebSocketProtocol::handleWriteDataEx(const CSessionPtr session, boost::system::error_code err)
{
	if (err)
	{
		LogErr("CCsgWebSocketProtocol::handleWriteDataEx handleWritet,ex=" << err.message());
		return -1;
	}
	else
	{
		LogDebug("CCsgWebSocketProtocol::handleWriteDataEx handleWritet.....");
		boost::system::error_code write_err;
		int wlen = session->getSocket()->write_some(boost::asio::buffer(_sendBuffer->getData(),_sendBuffer->getDataSize()), write_err);
		if (write_err)
		{
			LogErr("CCsgWebSocketProtocol::handleWriteDataEx write some2,ex=" << write_err.message());
			return -1;
		}
		else
		{
			LogDebug("CCsgWebSocketProtocol::handleWriteDataEx handleWritet complete,size=" << wlen);
		}
		_sendBuffer->popData(wlen);
	}
	return 0;
}

int csg::CCsgWebSocketProtocol::fetchFin(char *msg, int &pos)
{
	_fin = (unsigned char)msg[pos] >> 7;
	return 0;
}

int csg::CCsgWebSocketProtocol::fetchOpcode(char *msg, int &pos)
{
	_opCode = msg[pos] & 0x0f;
	pos++;
	return 0;
}

int csg::CCsgWebSocketProtocol::fetchMask(char *msg, int &pos)
{
	_mask = (unsigned char)msg[pos] >> 7;
	return 0;
}

int csg::CCsgWebSocketProtocol::fetchMaskingKey(char *msg, int& pos)
{
	if (_mask != 1)
		return 0;
	for (int i = 0; i < 4; i++)
		_masking_key[i] = msg[pos + i];
	pos += 4;
	return 0;
}

int csg::CCsgWebSocketProtocol::fetchPayloadLength(char *msg, int &pos)
{
	_payload_length = msg[pos] & 0x7f;
	pos++;
	if (_payload_length == 126) {
		uint16_t length = 0;
		memcpy(&length, msg + pos, 2);
		pos += 2;
		_payload_length = ntohs(length);
	}
	else if (_payload_length == 127) {
		uint32_t length = 0;
		memcpy(&length, msg + pos, 4);
		pos += 4;
		_payload_length = ntohl(length);
	}
	return 0;
}

int csg::CCsgWebSocketProtocol::fetchPayload(char *msg, int &pos)
{
	memset(_payload, 0, sizeof(_payload));
	if (_mask!= 1) {
		memcpy(_payload, msg + pos, _payload_length);
	}
	else {
		for (unsigned int i = 0; i < _payload_length; i++) {
			int j = i % 4;
			_payload[i] = msg[pos + i] ^ _masking_key[j];
		}
	}
	pos += _payload_length;
	//CMemToolHelper::hexDump(_payload, _payload_length,int(_payload));
	return 0;
}

void csg::CCsgWebSocketProtocol::printWebSocketDataInfo()
{
	LogDebug("======================websocket package info==========================");
	LogDebug("Fin:" << _fin);
	LogDebug("OpCode:" << _opCode);
	LogDebug("Mask:" << _mask);
	for (int i = 0; i < 4; i++) {
		LogDebug("Mask_key:" << _masking_key[i]);
	}
	LogDebug("PayloadLen:" << (long64_t)_payload_length);
	//LogDebug("PayLoad:" << _payload);
	LogDebug("======================websocket package info end==========================");
}

