#ifndef _ENGINE_NET_PROTOCOL_CSG_PROTOCOL_H_
#define _ENGINE_NET_PROTOCOL_CSG_PROTOCOL_H_

#include "protocol.h"
#include "../../lock/lock.h"

namespace csg
{
	class CCsgProtocol :public virtual IProtocol
	{
	public:
		virtual int handleRecvData(const CSessionPtr session,const void* inData ,const int len)override;

		virtual int handleSendData(const CSessionPtr session ,const void* data ,const int len)override;

		virtual int handleReadData(const CSessionPtr session)override;

		virtual int handleWriteData(const CSessionPtr session)override;

		virtual int pushMessage(const CSessionPtr session,const CMsgBlockPtr& mb)override;
	protected:
		virtual int handlePacket(const CSessionPtr session, const void *packageData, const int len);

		virtual int handleWriteDataEx(const CSessionPtr session, boost::system::error_code err);

	private:
		CLock _writeLock;
		CLock _readLock;
	
	};

	typedef CSmartPointShare<CCsgProtocol> CCsgProtocolPtr;
}
#endif