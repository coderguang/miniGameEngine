#include "engine/lock/lockObjectManager.h"


csg::CLockObjectManager::CLockObjectManager()
{
	CLockObjectManager::getSingletonLock();
	CLockObjectManager::getAtomicLock();
	CLockObjectManager::getCounterHandlerLock();
	CLockObjectManager::getLogLock();
}

csg::CLock& csg::CLockObjectManager::getSingletonLock()
{
	static csg::CLock singleLock;
	return singleLock;
}

csg::CLock& csg::CLockObjectManager::getAtomicLock()
{
	static CLock atomicLock;
	return atomicLock;
}

csg::CLock& csg::CLockObjectManager::getCounterHandlerLock(){

	static CLock counterHandlerLock;
	return counterHandlerLock;
}

csg::CLock& csg::CLockObjectManager::getLogLock()
{
	static csg::CLock logLock;
	return logLock;
}
