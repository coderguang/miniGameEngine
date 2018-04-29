#ifndef _ENGINE_NET_PROTOCOL_CSG_PROTOCOL_H_
#define _ENGINE_NET_PROTOCOL_CSG_PROTOCOL_H_

#include "protocol.h"
#include "../../lock/lock.h"

namespace csg
{
	class CCsgProtocol :public virtual IProtocol
	{
	public:
		CCsgProtocol(int recvSizeLimit,int recvBuffSize) :IProtocol(recvSizeLimit,recvBuffSize) {};
	};

	typedef CSmartPointShare<CCsgProtocol> CCsgProtocolPtr;
}
#endif