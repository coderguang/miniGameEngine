#include "engine/net/socket/socketManager.h"
#include "../../lock/lock.h"
#include "../../lock/lockObjectManager.h"
#include "framework/log/Log.h"
#include "framework/util/sysUtil.h"
#include "framework/util/typetransform.h"
#include "../../baseServer/SocketRecvTask.h"
#include "../../thread/threadManager.h"

using namespace csg;

CSocketManager* csg::CSocketManager::instance()
{
	CAutoLock l(CLockObjectManager::getSingletonLock());
	static CSocketManager ins;
	return &ins;
}

int csg::CSocketManager::init()
{
	if ( _isInit )
	{
		return CSG_RETURN_ERROR;
	}

#ifdef CSG_WIN
	_completionPort = CWinSocket::CreateIOCPPortInit();
	if ( NULL == _completionPort )
	{   // 创建IO内核对象失败
		CSG_RECORD_ERROR("CSocketManager::init CreateIoCompletionPort failed.");
		_coreError = true;
		return CSG_RETURN_ERROR;
	}
	//创建服务进程
	int createThreadAmount = CWinSocket::createIOCPThread(_workerThreadVec ,_completionPort ,CSocketRecvTask::workerThreadRun);
	if ( -1 == createThreadAmount )
	{
		CSG_RECORD_ERROR("CSocketManager::init createIOCPThread failed.");
		_coreError = true;
		return CSG_RETURN_ERROR;
	}
	CSG_LOG_DEBUG("CSocketManager::init createIOCPThread amount=" << ToStr(createThreadAmount));
#endif

	_isInit = true;
	return CSG_RETURN_OK;
}

#ifdef CSG_WIN
HANDLE csg::CSocketManager::getIOCPPort()
{
	return _completionPort;
}
#endif

void csg::CSocketManager::startListen(int family ,int type ,int protocol ,int port)
{
	CSocketRecvTask *task = new CSocketRecvTask();
	if ( CSG_RETURN_ERROR == task->init(AF_INET ,SOCK_STREAM ,0 ,port) )
	{
		CSG_LOG_ERR("CSocketManager::startListen init failed,port="<<ToStr(port));
		return;
	}
	task->startListen();
	_recvTaskList.push_back(task);

	CThreadManager::instance()->addTask(*task);
}


csg::CSocketManager::CSocketManager() :_coreError(false) ,_isInit(false)
{
#ifdef CSG_WIN
	_completionPort = NULL;
#endif

}

csg::CSocketManager::~CSocketManager()
{
	
}

