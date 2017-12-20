#ifndef _ENGINE_CORE_CSG_SERVER_H_
#define _ENGINE_CORE_CSG_SERVER_H_

#include "boost/asio.hpp"
#include "boost/core/noncopyable.hpp"
#include "engine/def/boost_def.h"
#include "framework/DesignPattern/Singleton.h"

namespace csg
{
	/*
	class CCsgServiceMgr:public virtual Singleton<CCsgServiceMgr>
	{
	public:

		boost_io_service_ptr get_io_service();

		boost_io_service_ptr get_log_service();

		boost_io_service_ptr get_db_service();

		boost_io_service_ptr get_update_dt_service();

		void run();

		void stop();
	protected:
		CCsgServiceMgr();
		~CCsgServiceMgr();

	private:
		boost_io_service_ptr _io_logic; 
		boost_io_service_ptr _io_log;
		boost_io_service_ptr _io_db;
		boost_io_service_ptr _io_update_dt;
		//for network io stream
		std::vector<boost_io_service_ptr> _io_pool;
		//worker
		std::vector<boost_work_ptr> _work_pool;
		std::vector<boost_thread_ptr> _thread_pool;
		int _next_io_service;
	};
	*/
}
#endif
