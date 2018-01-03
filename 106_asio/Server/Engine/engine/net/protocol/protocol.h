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
			_sendBuffer(CSerializeStreamPool::instance()->newObject()),_receiveHead(false)
		{

		}
		// IO�߳̽�������
		virtual int handleRecvData(const void* inData ,const int len) = 0;
		// �߼��߳�ѹ��
		virtual int handleSendData(const CSessionPtr& session ,const void* data ,const int len) = 0;
		// �߼��߳̽��
		virtual int handleReadData(const CSessionPtr& session) = 0;
		// IO�̷߳�������
		virtual int handleWriteData(const CSessionPtr& session) = 0;

	protected:
		CAutoSerializeStream _recvBuffer;
		CAutoSerializeStream _sendBuffer;
		SProtocolHead _protocolHead;
		bool _receiveHead;
	};

	typedef CSmartPointShare<IProtocol> IProtocolPtr;
}
#endif