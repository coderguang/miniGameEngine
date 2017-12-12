#ifndef _ENGINE_NET_SESSION_SESSION_H_
#define _ENGINE_NET_SESSION_SESSION_H_

#include "framework/SmartPoint/refObject.h"
#include "framework/SmartPoint/smartPoint.h"

namespace csg
{
	class CSession :public virtual CRefObject
	{
	public:
		CSession(int socketfd ,std::string& addr ,int port,bool isInner);

		int getSocketfd()const;

		void print(std::string info);

		virtual ~CSession();
	private:
		int _socketfd;
		std::string _remoteAddr;
		int _remotePort;
		bool _isClient;
	};
	typedef CSmartPointShare<CSession> CSessionPtr;
}
#endif