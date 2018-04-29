#ifndef _ENGINE_NET_PROTOCOL_CSG_WEB_SOCKET_PROTOCOL_H_
#define _ENGINE_NET_PROTOCOL_CSG_WEB_SOCKET_PROTOCOL_H_

#include "protocol.h"
#include "../../lock/lock.h"

namespace csg
{

	enum WS_FrameType
	{
		WS_CONTINUATION_FRAME=0x00,
		WS_TEXT_FRAME = 0x01,
		WS_BINARY_FRAME = 0x02,
		WS_CLOSING_FRAME = 0x08,
		WS_PING_FRAME = 0x09,
		WS_PONG_FRAME = 0x0A,
	};


	class CCsgWebSocketProtocol :public virtual IProtocol
	{
	public:
		CCsgWebSocketProtocol(int recvSizeLimit,int recvBuffSize) :IProtocol(recvSizeLimit,recvBuffSize),_is_complete_websocket_handshake(false)
			,_fin(),_opCode(),_mask(),_masking_key(),_payload(),_payload_length(){};

		virtual int handleRecvData(const CSessionPtr session,const void* inData ,const int len)override;

		virtual int handleSendData(const CSessionPtr session ,const void* data ,const int len)override;

	protected:


		int fetchFin(char *msg, int &pos);
		
		int fetchOpcode(char *msg, int &pos);

		int fetchMask(char *msg, int &pos);

		int fetchMaskingKey(char *msg, int& pos);

		int fetchPayloadLength(char *msg, int &pos);

		int fetchPayload(char *msg, int &pos);

		void printWebSocketDataInfo();
	private:
		bool _is_complete_websocket_handshake;
		CBytesBuffer _websocket_handshake_data;

	private:
		//websocket head info
		uint8_t _fin;
		uint8_t _opCode;
		uint8_t _mask;
		uint8_t _masking_key[4];
		uint64_t _payload_length;
		char _payload[PROTOCOL_RECV_MAX_SIZE_LIMIT_CLIENT*10];
	};

	typedef CSmartPointShare<CCsgWebSocketProtocol> CCsgWebSocketProtocolPtr;
}
#endif