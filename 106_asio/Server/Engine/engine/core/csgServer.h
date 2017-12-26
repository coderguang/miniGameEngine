#ifndef _ENGINE_CORE_CSG_SERVER_H_
#define _ENGINE_CORE_CSG_SERVER_H_

#include "framework/DesignPattern/Singleton.h"
#include "../baseServer/updateDtTask.h"
#include "../baseServer/loggerWritter.h"
#include "boost/smart_ptr/shared_ptr.hpp"


namespace csg
{

	class CCsgServer :public virtual Singleton<CCsgServer>
	{
	public:
		void init();
		
		void startUpdateDtServer();

		void startLogServer(std::string path,std::string logFileName);

		void stop();

	private:
		boost::shared_ptr<CUpdateDtTask> _dt;
		boost::shared_ptr<CLoggerWritterTask> _logger;
	};
}
#endif