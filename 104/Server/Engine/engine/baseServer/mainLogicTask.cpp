#include "engine/baseServer/mainLogicTask.h"
#include "../def/csg_def.h"
#include "../net/session/sessionManager.h"
#include "framework/timer/timerManager.h"

int csg::CMainLogicTask::run()
{
	CSG_LOG_SYS("CMainLogicTask::run start");
	std::unique_lock<CLock> lock(getLock());
	while ( !isExit() )
	{
		if ( isStop() )
		{
			CSG_LOG_SYS("CMainLogicTask::run waiting");
			_cv.wait(lock);
		}
		CDateTime now;
		//������Ϣ����
		CSessionManager::instance()->runNetMsgLoop();

		//��ʱ������
		CTimerManager::instance()->triggerTimer(now);

		CThread::sleep_for(100);
	}
	CSG_LOG_SYS("CMainLogicTask::run exit");
	return CSG_RETURN_OK;
}

