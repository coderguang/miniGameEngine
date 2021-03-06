#ifndef _ENGINE_CORE_CSG_SERVER_H_
#define _ENGINE_CORE_CSG_SERVER_H_

#include "framework/DesignPattern/Singleton.h"
#include "../baseServer/updateDtTask.h"
#include "../baseServer/loggerWritter.h"
#include "boost/smart_ptr/shared_ptr.hpp"
#include "../baseServer/SocketServer.h"
#include "../baseServer/mainLogicTask.h"


namespace csg
{

	class CCsgServer :public virtual Singleton<CCsgServer>
	{
	public:
		void init();
		
		void startUpdateDtServer();

		void startLogServer(std::string path,std::string logFileName,bool showConsole=false);

		void startMainLogicServer();

		bool startListenServer(int port, bool isInner, int sessionType);

		void stop();
	public:


	private:
		boost::shared_ptr<CUpdateDtTask> _dt;
		boost::shared_ptr<CLoggerWritterTask> _logger;
		boost::shared_ptr<CMainLogicTask> _logic;
		std::map<int, boost_CSocketServer_ptr> _mapSocket;
	};
}
#endif