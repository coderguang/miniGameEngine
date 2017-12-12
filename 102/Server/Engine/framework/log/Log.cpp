#include "framework/log/Log.h"
#include "engine/thread/thread.h"
#include <string>

void csg::CLogManager::add(const CLogRecord& newRecord)
{
	CAutoLock l(CLockObjectManager::getLogLock());
	_logRecord.push_back(newRecord);
}

void csg::CLogManager::add(const std::string& logStr ,ELogLevel level)
{
	CLogRecord logRecord(logStr,level);
	add(logRecord);
}

void csg::CLogManager::getLogRecord(SeqLogRecord& records)
{

	CAutoLock l(CLockObjectManager::getLogLock());
	records.swap(_logRecord);
	_logRecord.clear();
}

void csg::CLogRecord::appendLog(const std::string &str)
{
	logStr += str;
}

csg::CLogRecord& csg::operator<<( CLogRecord& out ,const std::string& str )
{
	out.appendLog(str);
	return out;
}
