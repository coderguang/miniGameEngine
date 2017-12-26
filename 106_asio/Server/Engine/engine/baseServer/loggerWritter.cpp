
#include "engine/baseServer/loggerWritter.h"
#include <iostream>
#include "framework/util/typetransform.h"
#include "engine/def/csg_def.h"
#include "engine/def/color_def.h"

#ifdef CSG_WIN
#include <direct.h>
#include <errno.h>
#define mkdir(x,y) _mkdir(x)
#endif
#ifdef CSG_LINUX
#include <sys/stat.h>
#endif
#include "../thread/thread.h"
#include "../core/csgIoMgr.h"


csg::CLoggerWritterTask::~CLoggerWritterTask()
{
	_ofs.flush();
	_ofs.close();
}

void csg::CLoggerWritterTask::setConsoleInfo(bool show)
{
	_consoleShow = show;
}

void csg::CLoggerWritterTask::setFileDir(const std::string dir,const std::string fileName)
{
	_dir = dir;
	_fileName = fileName;
	if ( -1 == mkdir(_dir.c_str() ,0777) )
	{
		if ( EEXIST != errno )
		{
			LogErr("CLoggerWritterTask::setFileDir,mkdir " << _dir << " error!,errno=" + ToStr(errno));
			return;
		}
	}
	LogSys("CLoggerWritterTask::setFileDir,mkdir " << _dir << " complete!");
}

void csg::CLoggerWritterTask::run()
{
	flush();
	CThread::sleep_for(500);
	CCsgIoMgr::instance()->getLogService()->post(boost::bind(&CLoggerWritterTask::run ,this));
}

void csg::CLoggerWritterTask::flush()
{
	CLogManager::instance()->getLogRecord(_logRecord);
	write();
}


void csg::CLoggerWritterTask::initLogMsgMap()
{
	_logMsgMap[ELogLevelUnknow] = "LogUnkonw";
	_logMsgMap[ELogSystem] = "LogSys";
	_logMsgMap[ELogError] = "LogErr";
	_logMsgMap[ELogWarnning] = "LogWarn";
	_logMsgMap[ELogInfo] = "LogInfo";
	_logMsgMap[ELogDebug] = "LogDebug";
}

void csg::CLoggerWritterTask::write()
{
	for ( SeqLogRecord::const_iterator it = _logRecord.begin(); it != _logRecord.end(); ++it )
	{
		write(*it);
	}
	_logRecord.clear();
}

void csg::CLoggerWritterTask::setInfoColor(const int logLv)
{
	int color = Color_White;

	if ( ELogInfo&logLv )
	{
		color = Color_Green;
	}
	if ( ELogDebug&logLv )
	{
		color = Color_Yellow;
	}
	if ( ELogWarnning&logLv )
	{
		color = Color_Pink;
	}
	if ( ELogSystem&logLv || ELogError&logLv )
	{
		color = Color_Red;
	}
	CColorHelper::setColor(color);
	std::cout << _logMsgMap[logLv];
	CColorHelper::setColor(Color_White);
}

void csg::CLoggerWritterTask::write(const CLogRecord& record)
{
#ifndef _DEBUG
	if ( ELogDebug == it->logLv )
		continue;
#endif

	std::string preLog = "[" + ToStr(record.pid) + "][" + ToStr(record.threadId) + "] " + record.logDt.asString()+":";
	std::string logMsg=
#ifndef _DEBUG
		 it->fileName + " " + it->functionName + ":" + ToStr(it->lineNum) + " "+
#endif
		  " : " + record.logStr;



	if ( _consoleShow )
	{
		std::cout << preLog;
		setInfoColor(record.logLv);
		std::cout << logMsg << std::endl;
	}
	std::string logFileName = record.logDt.asString("YYYY-MM-DD");
	if ( _lastWriteTotalDay != record.logDt.getTotalDay() )
	{
		if ( _ofs.is_open() )
			_ofs.close();
		_ofs.open(_dir + "/" +_fileName+"-"+logFileName + ".log" ,std::ios::app);
		if ( !_ofs.is_open() )
		{
			LogErr("csg::CLoggerWritterTask::write,cant open " << logFileName);
			return;
		}
		_lastWriteTotalDay = record.logDt.getTotalDay();
	}
	_ofs << preLog<<_logMsgMap[record.logLv]<<logMsg<< std::endl;
}



