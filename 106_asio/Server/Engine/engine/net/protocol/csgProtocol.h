#ifndef _ENGINE_NET_PROTOCOL_CSG_PROTOCOL_H_
#define _ENGINE_NET_PROTOCOL_CSG_PROTOCOL_H_

#include "protocol.h"

namespace csg
{
	class CCsgProtocol :public virtual IProtocol
	{
	public:
		virtual int handleRecvData(const void* inData ,const int len)override;

		virtual int handleSendData(const CSessionPtr& session ,const void* data ,const int len)override;

		virtual int handleReadData()
		{
			return 0;
		};

		virtual int handleWriteData()
		{
			return 0;
		};
	};

	typedef CSmartPointShare<CCsgProtocol> CCsgProtocolPtr;
}
#endif