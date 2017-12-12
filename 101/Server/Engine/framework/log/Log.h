
#ifndef _FRAMEWORK_LOG_LOG_H_
#define _FRAMEWORK_LOG_LOG_H_

#include <iostream>
#include "../datetime/datetime.h"
#include "../DesignPattern/Singleton.h"
#include <vector>
#include "engine/thread/thread.h"

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
		ELogLevel logLv;
		CDateTime logDt;
		std::string logStr;
		int threadId;
		int pid;
	};

	typedef std::vector<CLogRecord> SeqLogRecord;

	class CLogManager :public Singleton<CLogManager>
	{
	public:
		void add(const std::string& logStr ,ELogLevel level=ELogInfo);

		void getLogRecord(SeqLogRecord& records);
	protected:
		void add(const CLogRecord& newRecord);
	private:
		SeqLogRecord _logRecord;
	};
}

#define CSG_LOG_SYS(X) csg::CLogManager::instance()->add(X,csg::ELogSystem)

#define CSG_LOG_ERR(X) csg::CLogManager::instance()->add(X,csg::ELogError)

#define CSG_LOG_WARN(X) csg::CLogManager::instance()->add(X,csg::ELogWarnning)

#define CSG_LOG_TRACE(X) csg::CLogManager::instance()->add(X,csg::ELogInfo)

#define CSG_LOG_DEBUG(X) csg::CLogManager::instance(0->add(X,csg::ELogDebug)


#endif