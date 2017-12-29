#ifndef _ENGINE_PROTOCOL_PROTOCOL_H_
#define _ENGINE_PROTOCOL_PROTOCOL_H_

#include "framework/SmartPoint/refObject.h"
#include "framework/SmartPoint/smartPoint.h"
#include "../session/session.h"
#include "framework/DesignPattern/objectPool.h"

namespace csg
{

	struct SProtocolHead
	{
		uint_t msgSize;
	};

	static const size_t SIZE_OF_PROTOCOL_HEAD = sizeof(SProtocolHead);


	class CSession;

	typedef CSmartPointShare<CSession> CSessionPtr;

	class IProtocol :public virtual CRefObject
	{
	public:

		IProtocol() :_recvBuffer(CSerializeStreamPool::instance()->newObject()) ,
			_sendBuffer(CSerializeStreamPool::instance()->newObject())
		{

		}
		// IO线程接收数据
		virtual int handleRecvData(const void* inData ,const int len) = 0;
		// 逻辑线程压包
		virtual int handleSendData(const CSessionPtr& session ,const void* data ,const int len) = 0;
		// 逻辑线程解包
		virtual int handleReadData()
		{
			return 0;
		};
		// IO线程发送数据
		virtual int handleWriteData()
		{
			return 0;
		};

		char* getRecvDataPoint()
		{
			return const_cast<char*>(_recvBuffer->getData());
		};

		int getRecvDataSize()
		{
			return _recvBuffer->getDataSize();
		};

		void addRecvDataSize(int len)
		{
			_recvBuffer->addDataSize(len);
		};

	protected:
		CAutoSerializeStream _recvBuffer;
		CAutoSerializeStream _sendBuffer;
		SProtocolHead _protocolHead;
	};

	typedef CSmartPointShare<IProtocol> IProtocolPtr;
}
#endif