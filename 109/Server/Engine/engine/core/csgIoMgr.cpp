#include "boost/asio.hpp"
#include "framework/util/sysUtil.h"
#include "engine/core/csgIoMgr.h"
#include "framework/log/Log.h"
#include <boost/lexical_cast.hpp>

void csg::CCsgIoMgr::init()
{
	_nextIoService = 0;
	int sys_core_num = CSysUtil::getNumberOfProcessors();
	sys_core_num = sys_core_num / 2;
#ifdef _DEBUG
	sys_core_num = 1;
#endif
	sys_core_num = sys_core_num > 1 ? sys_core_num : 1;

	for(int i=0;i<sys_core_num;i++ ){
		boost_io_service_ptr io_service(new boost_io_service);
		boost_work_ptr work(new boost_work(*io_service));
		_ioPool.push_back(io_service);
		_workPool.push_back(work);
	}

	_ioLog = boost_io_service_ptr(new boost_io_service);
	boost_work_ptr wlog(new boost_work(*_ioLog));
	_workPool.push_back(wlog);

	_ioLogic = boost_io_service_ptr(new boost_io_service);
	boost_work_ptr wlogic(new boost_work(*_ioLogic));
	_workPool.push_back(wlogic);

	_ioUpdateDt = boost_io_service_ptr(new boost_io_service);
	boost_work_ptr wupdateDt(new boost_work(*_ioUpdateDt));
	_workPool.push_back(wupdateDt);

	_ioDb = boost_io_service_ptr(new boost_io_service);
	boost_work_ptr wdb(new boost_work(*_ioDb));
	_workPool.push_back(wdb);
	
}

boost_io_service_ptr csg::CCsgIoMgr::getIoService()
{
	CAutoLock l(_io_lock);
	if ( _nextIoService >= _ioPool.size() )
		_nextIoService = 0;
	return _ioPool[_nextIoService++];
}

boost_io_service_ptr csg::CCsgIoMgr::getLogService()
{
	return _ioLog;
}

boost_io_service_ptr csg::CCsgIoMgr::getDbService()
{
	return _ioDb;
}

boost_io_service_ptr csg::CCsgIoMgr::getUpdateDtService()
{
	return _ioUpdateDt;
}

boost_io_service_ptr csg::CCsgIoMgr::getLogicServer()
{
	return _ioLogic;
}

void csg::CCsgIoMgr::run()
{
	for ( int i = 0; i < _ioPool.size(); i++ )
	{
		boost_thread_ptr thread(new boost::thread(boost::bind(&boost_io_service::run ,_ioPool[i])));
// 		std::string id= boost::lexical_cast<std::string>(thread->get_id());
// 		LogSys("CCsgIoMgr::run,io_thread id " << id << " start...");
		_threadPool.push_back(thread);
	}

	LogInfo("CCsgIoMgr::run start io_server num is "<<(int)_ioPool.size());

	boost_thread_ptr threadLog(new boost::thread(boost::bind(&boost_io_service::run ,_ioLog)));
// 	std::string idstr = boost::lexical_cast<std::string>(threadLog->get_id());
// 	LogSys("CCsgIoMgr::run,threadLog id " << idstr << " start...");
	_threadPool.push_back(threadLog);

	boost_thread_ptr threadLogic(new boost::thread(boost::bind(&boost_io_service::run ,_ioLogic)));
// 	idstr = boost::lexical_cast<std::string>(threadLogic->get_id());
// 	LogSys("CCsgIoMgr::run,threadLogic id " << idstr << " start...");
	_threadPool.push_back(threadLogic);

	boost_thread_ptr threaddb(new boost::thread(boost::bind(&boost_io_service::run ,_ioDb)));
// 	idstr = boost::lexical_cast<std::string>(threaddb->get_id());
// 	LogSys("CCsgIoMgr::run,threaddb id " << idstr << " start...");
	_threadPool.push_back(threaddb);

	boost_thread_ptr threadUpdateDt(new boost::thread(boost::bind(&boost_io_service::run ,_ioUpdateDt)));
// 	idstr = boost::lexical_cast<std::string>(threadUpdateDt->get_id());
// 	LogSys("CCsgIoMgr::run,threadUpdateDt id " << idstr << " start...");
	_threadPool.push_back(threadUpdateDt);

	LogInfo("CCsgIoMgr::run start thread num is " << (int)_threadPool.size());
}

void csg::CCsgIoMgr::stop()
{
	LogSys("csg::CCsgIoMgr::stop");
	for ( int i = 0; i < _ioPool.size(); i++ )
	{
		_ioPool[i]->stop();
	}
	_ioLog->stop();
	_ioLogic->stop();
	_ioUpdateDt->stop();
	_ioDb->stop();

	for (int i = 0; i < _threadPool.size(); i++) {
// 		std::string id = boost::lexical_cast<std::string>(_threadPool[i]->get_id());
// 		std::cout<<"CCsgIoMgr::stop,wait id " << id << " end..."<<std::endl;
		_threadPool[i]->join();
	}
}

