
#ifndef _FRAMEWORK_LOG_LOG_H_
#define _FRAMEWORK_LOG_LOG_H_

#include <iostream>
#include "../datetime/datetime.h"
#include "../DesignPattern/Singleton.h"
#include <vector>
#include "engine/thread/thread.h"
#include "../util/sysUtil.h"

namespace csg
{

	enum ELogLevel{
		ELogLevelUnknow=0,
		ELogSystem=1,//ϵͳlog
		ELogError =2, //���ش���
		ELogWarnning =4, //����
		ELogInfo = 8,  //������Ϣ
		ELogDebug = 16, //������Ϣ
	};


	// log���ݹ���
	class CLogRecord
	{
	public:
		//Ĭ�ϲ�������Ч�ʸ���
		CLogRecord(const std::string& msg ,ELogLevel lv) :logLv(lv) ,logStr(msg) ,logDt(CDateTime()) ,threadId(CThread::threadId()) ,pid(CThread::pid())
		{
		
		}
		void appendLog(const std::string &str);

		ELogLevel logLv;
		CDateTime logDt;
		std::string logStr;
		int threadId;
		int pid;
	};

	typedef std::vector<CLogRecord> SeqLogRecord;

	CLogRecord& operator<< ( CLogRecord& out ,const std::string& str );

	class CLogManager :public Singleton<CLogManager>
	{
	public:
		void add(const std::string& logStr ,ELogLevel level=ELogInfo);

		void getLogRecord(SeqLogRecord& records);

		void add(const CLogRecord& newRecord);
	protected:
	
	private:
		SeqLogRecord _logRecord;
	};
}

#define CSG_LOG_SYS(X)\
	{\
	CLogRecord record("",csg::ELogSystem);\
	record<<X;\
	csg::CLogManager::instance()->add(record);\
	}
#define CSG_LOG_ERR(X) \
	{\
	CLogRecord record("",csg::ELogError);\
	record<<X;\
	csg::CLogManager::instance()->add(record);\
	}

#define CSG_LOG_WARN(X)\
	{\
	CLogRecord record("",csg::ELogWarnning);\
	record<<X;\
	csg::CLogManager::instance()->add(record);\
	}
#define CSG_LOG_INFO(X) \
	{\
	CLogRecord record("",csg::ELogInfo);\
	record<<X;\
	csg::CLogManager::instance()->add(record);\
	}

#define CSG_LOG_DEBUG(X) \
	{\
	CLogRecord record("",csg::ELogDebug);\
	record<<X;\
	csg::CLogManager::instance()->add(record);\
	}

#endif