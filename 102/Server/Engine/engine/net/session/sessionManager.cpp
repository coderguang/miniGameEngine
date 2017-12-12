#include "engine/net/session/sessionManager.h"
#include "session.h"


bool csg::CSessionManager::addSession(CSessionPtr& session)
{
	CAutoRecursiveLock l(getLock());

	if (isHaveSession(session->getSocketfd()))
	{
		CSG_LOG_DEBUG("CSessionManager::more than one");
		assert(false);
		return false;
	}
	_sessionMap[session->getSocketfd()] = session;
	return true;
}

bool csg::CSessionManager::removeSession(int socketfd)
{
	CAutoRecursiveLock l(getLock());
	
	if (!isHaveSession(socketfd) )
	{
		CSG_LOG_DEBUG("CSessionManager::no this session");
		assert(false);
		return false;
	}
	_sessionMap.erase(socketfd);
	return true;
}

csg::CSessionPtr csg::CSessionManager::getSession(int socketfd)
{
	CAutoRecursiveLock l(getLock());
	MapSession::const_iterator it = _sessionMap.find(socketfd);
	if ( it == _sessionMap.end() )
		return NULL;;
	return it->second;
}

csg::CRecursiveLock& csg::CSessionManager::getLock()
{
	static CRecursiveLock lock;
	return lock;
}

bool csg::CSessionManager::isHaveSession(int socketfd)
{
	CAutoRecursiveLock l(getLock());
	MapSession::iterator it = _sessionMap.find(socketfd);
	if ( it == _sessionMap.end() )
		return false;
	return true;
}

