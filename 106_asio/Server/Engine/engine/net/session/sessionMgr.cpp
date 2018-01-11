#include "engine/net/session/sessionMgr.h"
#include "../../core/csgIoMgr.h"

int csg::CSessionMgr::socketId = 100000;

bool csg::CSessionMgr::addSession(CSessionPtr session)
{
	LogDebug("CSessionMgr::addSession start...")
	CAutoLock l(_lock);
	int tmpId = socketId++;
	session->setSocketId(tmpId);
	MapTypeSession::iterator it = _sessionMap.find(session->getType());
	if (it == _sessionMap.end())
	{
		MapSession tmpMap;
		tmpMap[session->getSocketId()] = session;
		_sessionMap[session->getType()] = tmpMap;
	}
	else
	{
		it->second[session->getSocketId()] = session;
	}
	return true;
}

bool csg::CSessionMgr::delSession(CSessionPtr session)
{
	CAutoLock l(_lock);
	MapTypeSession::iterator it = _sessionMap.find(session->getType());
	if (it == _sessionMap.end())
	{
		return false;
	}
	else
	{
		MapSession::iterator idIt = it->second.find(session->getSocketId());
		if (idIt == it->second.end())
		{
			return false;
		}
		it->second.erase(idIt);
	}
	return true;
}

// void csg::CSessionMgr::runLoop()
// {
// 	CAutoLock l(_lock);
// 	for (MapTypeSession::iterator it = _sessionMap.begin();it != _sessionMap.end();++it)
// 		for (MapSession::iterator itEx = it->second.begin();itEx != it->second.end();++itEx) {
// 			if (itEx->second)
// 				itEx->second->handlePacketRecvData();
// 		}
// 	CThread::sleep_for(100);
// 	CCsgIoMgr::instance()->getLogicServer()->post(boost::bind(&CSessionMgr::runLoop, this));
// }

void csg::CSessionMgr::disconnectAll()
{
	CAutoLock l(_lock);
	for (MapTypeSession::iterator it = _sessionMap.begin();it != _sessionMap.end();++it)
		for (MapSession::iterator itEx = it->second.begin();itEx != it->second.end();++itEx) {
			if (itEx->second)
				itEx->second->getSocket()->close();
		}

}

