#include <iostream>
#include "engine/core/csgServer.h"
#include "TestCmdManager.h"
#include "log/TestLog.h"
#include "framework/util/CCmdManager.h"

using namespace csg;

void startSimple()
{
	//testDateTime();
	testLog();
}

void start_main(int argc ,char** argv)
{
	startRegistCmd();
	do
	{
		std::string inputStr;
		getline(std::cin ,inputStr);
		if ( "q" == inputStr )
		{
			break;
		}
		try
		{
			if ( !CCmdManager::instance()->dealCmd(inputStr) )
			{
				LogErr(inputStr << " not a correct commands!");
				CCmdManager::instance()->printCmd();
			}
		} catch ( std::exception ex )
		{
			LogErr("startSimpleMain deal cmd occure exception,ex=" << ex.what());
		} catch ( ... )
		{
			LogErr("startSimpleMain deal cmd occure exception unknow exception");
		}

	} while ( true );

}

int main(int argc ,char **argv)
{

	LogDebug("Program run in below environment !!!");
#ifdef _DEBUG
	LogDebug("_DEBUG set");
#endif

#ifdef CSG_WIN
	LogDebug("CSG_WIN set");
#endif

#ifdef CSG_LINUX
	LogDebug("CSG_LINUX set");
#endif

	CCsgServer::instance()->init();

	CCsgServer::instance()->startUpdateDtServer();
	CCsgServer::instance()->startLogServer("./log" ,"TestLog");

	CCsgServer::instance()->startMainLogicServer();

	start_main(argc ,argv);

	CCsgServer::instance()->stop();

	cin.get();
	return 0;
}