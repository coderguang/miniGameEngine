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
	
	return IProtocol::handleRecvData(session,_payload,_payload_length);
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

	return IProtocol::handleSendData(session,frame, frameHeaderSize + len);
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

