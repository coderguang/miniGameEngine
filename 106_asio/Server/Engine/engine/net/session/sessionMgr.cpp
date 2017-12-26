#include "engine/net/session/sessionMgr.h"

int csg::CSessionMgr::socketId = 100000;

bool csg::CSessionMgr::addSession(CSessionPtr& session)
{
	CAutoLock l(_lock);
	int tmpId = socketId++;
	session->setSocketId(tmpId);
	MapTypeSession::iterator it = _sessionMap.find(session->getType());
	if ( it == _sessionMap.end() )
	{
		MapSession tmpMap;
		tmpMap[session->getSocketId()] = session;
		_sessionMap[session->getType()] = tmpMap;
	} else
	{
		it->second[session->getSocketId()] = session;
	}
	return true;
}

bool csg::CSessionMgr::delSession(CSessionPtr& session)
{
	CAutoLock l(_lock);
	MapTypeSession::iterator it = _sessionMap.find(session->getType());
	if ( it == _sessionMap.end() )
	{
		return false;
	} else
	{
		MapSession::iterator idIt = it->second.find(session->getSocketId());
		if ( idIt == it->second.end() )
		{
			return false;
		}
		it->second.erase(idIt);
	}
	return true;
}

