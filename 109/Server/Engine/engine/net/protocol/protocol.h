#ifndef _ENGINE_PROTOCOL_PROTOCOL_H_
#define _ENGINE_PROTOCOL_PROTOCOL_H_

#include "framework/SmartPoint/refObject.h"
#include "framework/SmartPoint/smartPoint.h"
#include "../session/session.h"
#include "framework/DesignPattern/objectPool.h"
#include "../../mq/msgBlock.h"

namespace csg
{

	struct SProtocolHead
	{
		uint_t msgSize;
	};

	static const size_t SIZE_OF_PROTOCOL_HEAD = sizeof(SProtocolHead);

	static const int PROTOCOL_RECV_MAX_SIZE_LIMIT_CLIENT = 4096;  //客户端单包大小限制
	static const int PROTOCOL_RECV_BUFF_MAX_SIZE_LIMIT_CLIENT = 4096 * 250; //客户端总buff大小限制,超出时会断开连接
	static const int PROTOCOL_RECV_MAX_SIZE_LIMIT_SERVER = 4096 * 100; //服务器单包大小限制

	class CSession;

	typedef CSmartPointShare<CSession> CSessionPtr;

	class IProtocol:public virtual CRefObject
	{
	public:

		IProtocol(int recvSizeLimit,int recvBuffSizeLimit) :_recvBuffer(CSerializeStreamPool::instance()->newObject()),
			_sendBuffer(CSerializeStreamPool::instance()->newObject()), _receiveHead(false), _maxRecvSize(recvSizeLimit),_maxRecvBuffSize(recvBuffSizeLimit)
		{

		}

		virtual ~IProtocol();
		// IO线程接收数据
		virtual int handleRecvData(const CSessionPtr session, const void* inData ,const int len);
		// 逻辑线程压包
		virtual int handleSendData(const CSessionPtr session ,const void* data ,const int len);

		virtual int pushMessage(const CSessionPtr session,const CMsgBlockPtr& mb);

	protected:
		// 逻辑线程解包
		virtual int handleReadData(const CSessionPtr session);

		virtual int handleWriteData(const CSessionPtr session, boost::system::error_code err);

		virtual int handlePacket(const CSessionPtr session, const void *packageData, const int len);

	private:
		CAutoSerializeStream _recvBuffer;
		CAutoSerializeStream _sendBuffer;
		SProtocolHead _protocolHead;
		bool _receiveHead;
		int _maxRecvSize;
		int _maxRecvBuffSize;

		CLock _writeLock;
		CLock _readLock;
	};

	typedef CSmartPointShare<IProtocol> IProtocolPtr;
}
#endif