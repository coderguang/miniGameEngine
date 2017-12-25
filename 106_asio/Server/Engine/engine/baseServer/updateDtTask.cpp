#include "engine/baseServer/updateDtTask.h"
#include <iostream>
#include <mutex>
#include "framework/log/Log.h"

int csg::CUpdateDtTask::run()
{
	/*
	LogSys("CUpdateDtTask::run start");
	std::unique_lock<CLock> lock(getLock());
	while ( !isExit() )
	{
		if ( isStop() )
		{
			LogSys("CUpdateDtTask::run waiting");
			_cv.wait(lock);
		}
		CThread::sleep_for(1); //1ms 更新一次线程时间
		CDateTime::updateThreadDt();
	}
	LogSys("CUpdateDtTask::run exit");
	*/
	return CSG_RETURN_OK;
	
}

