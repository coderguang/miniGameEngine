
#ifndef _FRAMEWORK_LOG_LOG_H_
#define _FRAMEWORK_LOG_LOG_H_

#include <iostream>
#include "../datetime/datetime.h"
#include "../DesignPattern/Singleton.h"
#include <vector>
#include "../util/sysUtil.h"
#include "../DesignPattern/objectPool.h"

namespace csg
{

	enum ELogLevel{
		ELogLevelUnknow=0,
		ELogSystem=1,//系统log
		ELogError =2, //严重错误
		ELogWarnning =4, //警告
		ELogInfo = 8,  //常规信息
		ELogDebug = 16, //调试信息
	};


	// log数据管理
	class CLogRecord
	{
	public:
		void init(const std::string& msg ,ELogLevel lv,std::string fileN="default",std::string functionN="default",int lineN=0) 
		{
			logStr = msg;
			logLv = lv;
			//pid = CThread::pid();
			pid = 0;
			//threadId = CThread::threadId();
			logDt = CDateTime();
			fileName = fileN;
			functionName = functionN;
			lineNum = lineN;
		}
		void appendLog(const std::string &str);

		void reset()
		{
			logLv = ELogLevelUnknow;
			logDt = CDateTime();
			logStr = "";
			functionName = "";
			fileName = "";
			lineNum = 0;
			threadId = 0;
			pid = 0;
		}

		ELogLevel logLv;
		CDateTime logDt;
		std::string logStr;
		std::string functionName;
		std::string fileName;
		int lineNum;
		int threadId;
		int pid;
	};

	typedef std::vector<CLogRecord> SeqLogRecord;

	CLogRecord& operator<< ( CLogRecord& out ,const std::string& str );

	CLogRecord& operator<< ( CLogRecord& out ,const int v );

	CLogRecord& operator<< ( CLogRecord& out ,const double v );

	CLogRecord& operator<< ( CLogRecord& out ,const long64_t v );

	//这个bool类型会导致 字符串变量被优先匹配
	//CLogRecord& operator<< ( CLogRecord& out ,const bool v );


	class CLogManager :public Singleton<CLogManager>
	{
	public:
		void getLogRecord(SeqLogRecord& records);

		void add(const CLogRecord& newRecord);
	protected:
	
	private:
		SeqLogRecord _logRecord;
	};
}

#define LogSys(X)\
	{\
    CAutoLogRecord record(CLogRecordPool::instance()->newObject());\
    record->init("" ,csg::ELogSystem ,__FILE__ ,__FUNCTION__ ,__LINE__); \
    *record<<X;\
    csg::CLogManager::instance()->add(*record);\
	}
#define LogErr(X) \
	{\
    CAutoLogRecord record(CLogRecordPool::instance()->newObject());\
    record->init("",csg::ELogError,__FILE__,__FUNCTION__,__LINE__);\
    *record<<X;\
    csg::CLogManager::instance()->add(*record);\
	}

#define LogWarn(X)\
	{\
    CAutoLogRecord record(CLogRecordPool::instance()->newObject());\
	record->init("",csg::ELogWarnning,__FILE__,__FUNCTION__,__LINE__);\
	*record<<X;\
	csg::CLogManager::instance()->add(*record);\
	}
#define LogInfo(X) \
	{\
    CAutoLogRecord record(CLogRecordPool::instance()->newObject());\
	record->init("",csg::ELogInfo,__FILE__,__FUNCTION__,__LINE__);\
	*record<<X;\
	csg::CLogManager::instance()->add(*record);\
	}

#define LogDebug(X) \
	{\
    CAutoLogRecord record(CLogRecordPool::instance()->newObject());\
	record->init("",csg::ELogDebug,__FILE__,__FUNCTION__,__LINE__);\
	*record<<X;\
	csg::CLogManager::instance()->add(*record);\
	}

#endif