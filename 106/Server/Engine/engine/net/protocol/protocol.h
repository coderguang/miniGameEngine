#ifndef _ENGINE_NET_PROTOCOL_PROTOCOL_H_
#define _ENGINE_NET_PROTOCOL_PROTOCOL_H_

#include "../../lock/lock.h"
#include "../../serialize/serializestream.h"
#include "protocoldef.h"
#include "framework/SmartPoint/smartPoint.h"
#include "framework/SmartPoint/refObject.h"
#include "framework/DesignPattern/objectPool.h"
#include "../../mq/msgBlock.h"
#include "../session/session.h"

namespace csg
{

	class CSession;

	typedef CSmartPointShare<CSession> CSessionPtr;

	//ÿ��Session����һ��protocol
	class CProtocol:public virtual CRefObject
	{
	public:
		CProtocol();

		virtual ~CProtocol();
		// IO �߳̽�������
		virtual int handleRecvData(const void* inData ,const int len);
		// IO �̷߳�������
		virtual int handleSendData(const CSessionPtr& session,const void* data ,const int len);
		//�߼����̴߳�������
		virtual bool handlePacket(const CSessionPtr& session);

		virtual int pushMessage(const CSessionPtr& session ,const CMsgBlockPtr& mb);

	protected:
		virtual bool handlePacket(const CSessionPtr& session,const void *inData ,const int len);

	protected:
		CRecursiveLock& getLock();

	private:
		CRecursiveLock _lock;
		CAutoSerializeStream _buffer; //����IO�н��յ����ݴ��������
		SProtocolHead _protocolHead;
		bool _receiveHead;
	};

	typedef CSmartPointShare<CProtocol> CProtocolPtr;
}

#endif