#include "engine/baseServer/mainLogicTask.h"
#include "../def/csg_def.h"
#include "framework/timer/timerManager.h"

int csg::CMainLogicTask::run()
{
	/*
	LogSys("CMainLogicTask::run start");
	std::unique_lock<CLock> lock(getLock());
	while ( !isExit() )
	{
		if ( isStop() )
		{
			LogSys("CMainLogicTask::run waiting");
			_cv.wait(lock);
		}
		CDateTime now;
		//网络消息处理
		//CSessionManager::instance()->runNetMsgLoop();

		//定时器触发
		CTimerManager::instance()->triggerTimer(now);

		CThread::sleep_for(100);
	}
	LogSys("CMainLogicTask::run exit");
	*/
	return CSG_RETURN_OK;
}

