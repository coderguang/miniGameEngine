#include "engine/baseServer/SocketSendTask.h"
#include "framework/log/Log.h"
#include "../mq/msgQueue.h"
#include "../thread/thread.h"

using namespace csg;
int csg::CSocketSendTask::svn_run(void* task)
{
	CSocketSendTask *t = (CSocketSendTask*) task;
	if ( !t )
	{
		assert(false);
		return CSG_RETURN_ERROR;
	}
	t->run();
	return CSG_RETURN_OK;
}

int csg::CSocketSendTask::run()
{
	LogSys("CSocketSendTask::start ");

	std::unique_lock<CLock> lock(getLock());
	while ( !isExit() )
	{
		if ( isStop() )
		{
			LogSys("CSocketSendTask::run waiting");
			_cv.wait(lock);
		}
		CMsgQueue::instance()->runLoop();
		CThread::sleep_for(100);
	}
	CMsgQueue::instance()->runLoop();
	LogSys("CSocketSendTask::run exit");
	return 0;
}

