#include "engine/baseServer/updateDtTask.h"
#include <iostream>
#include <mutex>
#include "framework/log/Log.h"
#include "../thread/thread.h"
#include "../core/csgIoMgr.h"

void csg::CUpdateDtTask::run()
{
	CThread::sleep_for(1); //1ms 更新一次线程时间
	CDateTime::updateThreadDt();
	CCsgIoMgr::instance()->getUpdateDtService()->post(boost::bind(&CUpdateDtTask::run ,this));
}

