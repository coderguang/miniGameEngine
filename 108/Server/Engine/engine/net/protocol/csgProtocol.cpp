#include "engine/net/protocol/csgProtocol.h"
#include "framework/util/endian.h"
#include "../../rpc/rmidef.h"
#include "../../mq/msgBlock.h"
#include "../../rpc/rmiObjectAdapter.h"
#include "../../core/csgIoMgr.h"
#include "../session/sessionMgr.h"

int csg::CCsgProtocol::handleRecvData(const CSessionPtr session,const void* inData, const int len)
{
	CAutoLock l(_readLock);

	if (_recvBuffer->getDataSize() + len > _maxRecvBuffSize) {
		LogErr(__FUNCTION__ << " recieve buffer size out of limit,now=" << (_recvBuffer->getDataSize() + len )<< ",limit=" << _maxRecvBuffSize);
		//超过缓冲区大小时直接断开连接--由上层断开
		return -1;
	}
	if (_receiveHead&&_protocolHead.msgSize > _maxRecvBuffSize) {
		LogErr(__FUNCTION__ << " protocol head msg size error,now=" << (int)_protocolHead.msgSize << ",limit=" << _maxRecvBuffSize);
		return -1;
	}
	_recvBuffer->append(inData, len);

	CCsgIoMgr::instance()->getLogicServer()->post(boost::bind(&CCsgProtocol::handleReadData,this,session));
	return 0;
}

int csg::CCsgProtocol::handleSendData(const CSessionPtr session, const void* data, const int len)
{
	CAutoLock l(_writeLock);
	_sendBuffer->append(data, len);
	session->getSocket()->async_write_some(boost::asio::null_buffers(), boost::bind(&CCsgProtocol::handleWriteDataEx,this, session, boost::asio::placeholders::error));
	return 0;
}

int csg::CCsgProtocol::handleReadData(const CSessionPtr session)
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
					LogErr(__FUNCTION__ << ",csg ex=" << ex.what());
				}
				catch (std::exception& ex) {
					LogErr(__FUNCTION__ << ",std ex=" << ex.what());
				}
				catch (...) {
					LogErr(__FUNCTION__ << " unknow exception")
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

int csg::CCsgProtocol::handleWriteData(const CSessionPtr session)
{

	return 0;
}

int csg::CCsgProtocol::pushMessage(const CSessionPtr session,const CMsgBlockPtr& mb)
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

int csg::CCsgProtocol::handlePacket(const CSessionPtr session, const void *packageData, const int len)
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

int csg::CCsgProtocol::handleWriteDataEx(const CSessionPtr session, boost::system::error_code err)
{
	if (err)
	{
		LogErr("CCsgProtocol::handleWriteDataEx handleWritet,ex=" << err.message());
		return -1;
	}
	else
	{
		LogDebug("CCsgProtocol::handleWriteDataEx handleWritet.....");
		boost::system::error_code write_err;
		int wlen = session->getSocket()->write_some(boost::asio::buffer(_sendBuffer->getData(),_sendBuffer->getDataSize()), write_err);
		if (write_err)
		{
			LogErr("CCsgProtocol::handleWriteDataEx write some2,ex=" << write_err.message());
			return -1;
		}
		else
		{
			LogDebug("CCsgProtocol::handleWriteDataEx handleWritet complete,size=" << wlen);
		}
		_sendBuffer->popData(wlen);
	}
	return 0;
}

