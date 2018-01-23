#include "engine/baseServer/mainLogicTask.h"
#include "../def/csg_def.h"
#include "framework/timer/timerManager.h"
#include "../core/csgIoMgr.h"

void csg::CMainLogicTask::run()
{
	CDateTime now;
	CTimerManager::instance()->triggerTimer(now);
	CThread::sleep_for(100);
	CCsgIoMgr::instance()->getLogicServer()->post(boost::bind(&CMainLogicTask::run, this));
}

