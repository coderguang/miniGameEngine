#include "engine/core/csgServer.h"
#include "csgIoMgr.h"
#include "../baseServer/loggerWritter.h"
#include "boost/asio/io_service.hpp"
#include "framework/datetime/datetime.h"
#include "../baseServer/updateDtTask.h"
#include "../net/session/sessionMgr.h"
#include "../baseServer/SocketServer.h"

void csg::CCsgServer::init()
{
	CCsgIoMgr::instance()->init();
	CCsgIoMgr::instance()->run();
}

void csg::CCsgServer::startUpdateDtServer()
{
	_dt= boost::shared_ptr<CUpdateDtTask>(new CUpdateDtTask());
	CCsgIoMgr::instance()->getUpdateDtService()->post(boost::bind(&CUpdateDtTask::run,_dt));
	LogInfo("start update dt server complete!");
}

void csg::CCsgServer::startLogServer(std::string path ,std::string logFileName)
{
	_logger= boost::shared_ptr<CLoggerWritterTask>(new CLoggerWritterTask());
	_logger->setFileDir(path ,logFileName);
#ifdef _DEBUG
	_logger->setConsoleInfo(true);
#endif
	_logger->initLogMsgMap();
	CCsgIoMgr::instance()->getLogService()->post(boost::bind(&CLoggerWritterTask::run ,_logger));

	LogInfo("start log server complete!");
}

void csg::CCsgServer::startMainLogicServer()
{
	CCsgIoMgr::instance()->getLogicServer()->post(boost::bind(&CSessionMgr::runLoop, CSessionMgr::instance()));
	LogInfo("start update main logic server complete!");
}

bool csg::CCsgServer::startListenServer(int port, bool isInner, int sessionType)
{
	std::map<int, boost_CSocketServer_ptr>::iterator it = _mapSocket.find(port);
	if (it != _mapSocket.end()) {
		LogErr("CCsgServer::startListenServer,duplicate port=" << port);
		assert(false);
		return false;
	}

	boost_CSocketServer_ptr srv(new CSocketServer());
	srv->init(port, isInner, sessionType);
	srv->startListen();
	_mapSocket[port] = srv;
	LogInfo("start listen server complete!port="<<port);
	return true;
}

void csg::CCsgServer::stop()
{
	CCsgIoMgr::instance()->stop();
}
