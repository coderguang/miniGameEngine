#ifndef _ENGINE_PROTOCOL_PROTOCOL_H_
#define _ENGINE_PROTOCOL_PROTOCOL_H_

#include "framework/SmartPoint/refObject.h"
#include "framework/SmartPoint/smartPoint.h"
#include "../session/session.h"

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
		virtual int handleRecvData(const void* inData ,const int len) = 0;
		
		virtual int handleSendData(const CSessionPtr& session ,const void* data ,const int len)=0;
	protected:
		CAutoSerializeStream _buffer;
		SProtocolHead _protocolHead;
	};
}
#endif