#ifndef _ENGINE_NET_SESSION_SESSION_MGR_H_
#define _ENGINE_NET_SESSION_SESSION_MGR_H_

#include "framework/DesignPattern/Singleton.h"
#include "session.h"
#include "../../lock/lock.h"

namespace csg
{
	typedef std::map<int ,CSessionPtr> MapSession;
	typedef std::map<int ,MapSession> MapTypeSession;

	class CSessionMgr :public virtual Singleton<CSessionMgr>
	{
	public:
		bool addSession(CSessionPtr& session);

		bool delSession(CSessionPtr& session);
	private:
		static int socketId;
		MapTypeSession _sessionMap;
		CLock _lock;
	};
}
#endif