#include "boost/asio.hpp"
#include "engine/core/csgServer.h"
#include "framework/util/sysUtil.h"
//#include "boost/thread/detail/thread.hpp"


csg::CCsgService::CCsgService()
{
	/*
	_next_io_service = 0;
	int sys_core_num = CSysUtil::getNumberOfProcessors();
	sys_core_num = sys_core_num / 2;
#ifdef _DEBUG
	sys_core_num = 1;
#endif
	sys_core_num = sys_core_num > 0 ? sys_core_num : 1;
	
	for(int i=0;i<sys_core_num;i++ ){
		boost_io_service_ptr io_service(new boost::asio::io_service);
		boost_work_ptr work(new boost::asio::io_service::work(*io_service));
		_io_pool.push_back(io_service);
		_work_pool.push_back(work);
	}

	_io_log = boost_io_service_ptr(new boost::asio::io_service);
	boost_work_ptr wlog(new boost::asio::io_service::work(*_io_log));
	_work_pool.push_back(wlog);

	_io_logic = boost_io_service_ptr(new boost::asio::io_service);
	boost_work_ptr wlogic(new boost::asio::io_service::work(*_io_logic));
	_work_pool.push_back(wlogic);

	_io_update_dt = boost_io_service_ptr(new boost::asio::io_service);
	boost_work_ptr wupdateDt(new boost::asio::io_service::work(*_io_update_dt));
	_work_pool.push_back(wupdateDt);

	_io_db = boost_io_service_ptr(new boost::asio::io_service);
	boost_work_ptr wdb(new boost::asio::io_service::work(*_io_db));
	_work_pool.push_back(wdb);
	*/
}

csg::CCsgService::~CCsgService()
{

}

boost_io_service_ptr csg::CCsgService::get_io_service()
{
	if ( _next_io_service >= _io_pool.size() )
		_next_io_service = 0;
	return _io_pool[_next_io_service++];
}

boost_io_service_ptr csg::CCsgService::get_log_service()
{
	return _io_log;
}

boost_io_service_ptr csg::CCsgService::get_db_service()
{
	return _io_db;
}

boost_io_service_ptr csg::CCsgService::get_update_dt_service()
{
	return _io_update_dt;
}

void csg::CCsgService::run()
{
	/*
	for ( int i = 0; i < _io_pool.size(); i++ )
	{
		boost_thread_ptr thread(new boost::thread(boost::bind(&boost::asio::io_service::run ,_io_pool[i])));
		_thread_pool.push_back(thread);
	}

	boost_thread_ptr threadLog(new boost::thread(boost::bind(&boost::asio::io_service::run ,_io_log)));
	_thread_pool.push_back(threadLog);

	boost_thread_ptr threadLogic(new boost::thread(boost::bind(&boost::asio::io_service::run ,_io_logic)));
	_thread_pool.push_back(threadLogic);

	boost_thread_ptr threaddb(new boost::thread(boost::bind(&boost::asio::io_service::run ,_io_db)));
	_thread_pool.push_back(threaddb);

	boost_thread_ptr threadUpdateDt(new boost::thread(boost::bind(&boost::asio::io_service::run ,_io_update_dt)));
	_thread_pool.push_back(threadUpdateDt);
	*/
}

void csg::CCsgService::stop()
{
	/*
	for ( int i = 0; i < _io_pool.size(); i++ )
	{
		_io_pool[i]->stop();
	}
	_io_log->stop();
	_io_logic->stop();
	_io_update_dt->stop();
	_io_db->stop();

	for ( int i = 0; i < _thread_pool.size(); i++ )
		_thread_pool[i]->join();
		*/
}

