#ifndef _ENGINE_CORE_CSG_IOMGR_H_
#define _ENGINE_CORE_CSG_IOMGR_H_

#include "boost/asio.hpp"
#include "boost/core/noncopyable.hpp"
#include "engine/def/boost_def.h"
#include "framework/DesignPattern/Singleton.h"

namespace csg
{
	
	class CCsgIoMgr:public virtual Singleton<CCsgIoMgr>
	{
	public:

		boost_io_service_ptr getIoService();

		boost_io_service_ptr getLogService();

		boost_io_service_ptr getDbService();

		boost_io_service_ptr getUpdateDtService();

		void run();

		void stop();

		void init();
	protected:


	private:
		boost_io_service_ptr _ioLogic; 
		boost_io_service_ptr _ioLog;
		boost_io_service_ptr _ioDb;
		boost_io_service_ptr _ioUpdateDt;
		//for network io stream
		std::vector<boost_io_service_ptr> _ioPool;
		//worker
		std::vector<boost_work_ptr> _workPool;
		std::vector<boost_thread_ptr> _threadPool;
		int _nextIoService;
	};
	
}
#endif
