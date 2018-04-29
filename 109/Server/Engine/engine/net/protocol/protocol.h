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

	static const int PROTOCOL_RECV_MAX_SIZE_LIMIT_CLIENT = 4096;  //�ͻ��˵�����С����
	static const int PROTOCOL_RECV_BUFF_MAX_SIZE_LIMIT_CLIENT = 4096 * 250; //�ͻ�����buff��С����,����ʱ��Ͽ�����
	static const int PROTOCOL_RECV_MAX_SIZE_LIMIT_SERVER = 4096 * 100; //������������С����

	class CSession;

	typedef CSmartPointShare<CSession> CSessionPtr;

	class IProtocol:public virtual CRefObject
	{
	public:

		IProtocol(int recvSizeLimit,int recvBuffSizeLimit) :_recvBuffer(CSerializeStreamPool::instance()->newObject()),
			_sendBuffer(CSerializeStreamPool::instance()->newObject()), _receiveHead(false), _maxRecvSize(recvSizeLimit),_maxRecvBuffSize(recvBuffSizeLimit)
		{

		}
		// IO�߳̽�������
		virtual int handleRecvData(const CSessionPtr session, const void* inData ,const int len);
		// �߼��߳�ѹ��
		virtual int handleSendData(const CSessionPtr session ,const void* data ,const int len);

		virtual int pushMessage(const CSessionPtr session,const CMsgBlockPtr& mb);

	protected:
		// �߼��߳̽��
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