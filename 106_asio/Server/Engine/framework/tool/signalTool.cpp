#include "framework/tool/signalTool.h"
#include "../log/Log.h"
#include <signal.h>


void csg::signalHandleExit(int signalNum)
{
	LogSys("csg::signalHandleExit ,exit");
	CThread::sleep_for(2000);
	exit(signalNum);
}

void csg::signalHandleKill(int signalNum)
{
	LogSys("csg::signalHandleKill ,be kill");
	CThread::sleep_for(2000);
	exit(signalNum);
}

void csg::registSignalHandle()
{
	signal(SIGINT, &csg::signalHandleExit);
	signal(SIGTERM, &csg::signalHandleKill);
}

