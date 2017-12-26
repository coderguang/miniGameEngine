#include "engine/core/csgServer.h"
#include "csgIoMgr.h"
#include "../baseServer/loggerWritter.h"
#include "boost/asio/io_service.hpp"
#include "framework/datetime/datetime.h"
#include "../baseServer/updateDtTask.h"

void csg::CCsgServer::init()
{
	CCsgIoMgr::instance()->init();
	CCsgIoMgr::instance()->run();
}

void csg::CCsgServer::startUpdateDtServer()
{
	_dt= boost::shared_ptr<CUpdateDtTask>(new CUpdateDtTask());
	CCsgIoMgr::instance()->getUpdateDtService()->post(boost::bind(&CUpdateDtTask::run,_dt));
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
}

void csg::CCsgServer::stop()
{
	CCsgIoMgr::instance()->stop();
}
