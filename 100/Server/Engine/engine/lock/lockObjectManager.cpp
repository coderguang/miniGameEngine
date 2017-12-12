#include "engine/lock/lockObjectManager.h"


csg::CLockObjectManager::CLockObjectManager()
{
	CLockObjectManager::getSingletonLock();
	CLockObjectManager::getAtomicLock();
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