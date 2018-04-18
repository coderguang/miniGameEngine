#include <iostream>
#include "engine/core/csgServer.h"
#include "TestCmdManager.h"
#include "log/TestLog.h"
#include "framework/util/CCmdManager.h"
#include "lua/testLua.h"
#include "test/rapidjsonTest.h"
#include "test/asioIOserviceTest.h"
#include "test/new_net_core.h"
#include "framework/tool/memTool.h"

using namespace csg;

void start_simple()
{
	//testDateTime();
	//testLog();
	//testRapidJson();
	//testZeroWorkIOservice();

	CCsgServer::instance()->startListenServer(9201, false, ESessionTypeClient);
// 	testWebSocketHandleShake();

}

void start_main(int argc ,char** argv)
{
	startRegistCmd();
	start_simple();
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


void start_lua() {

	lua_State *L = luaL_newstate();

	luaL_openlibs(L);

	luaL_dofile(L, "../LuaScript/Main.lua");
	//luaL_dofile(L, "../../LuaScript/Main.lua");

	lua_close(L);

	LogDebug("start lua ok");
	return;

}

void testfytx() {
	net_new_core_csg.init();
	net_new_core_csg.run();
	onlyQForExit();
	net_new_core_csg.stop();
}

void testCsg() {
// 	new_net_sev.init();
// 	new_net_sev.run();
// 	onlyQForExit();
// 	new_net_sev.stop();
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
	CCsgServer::instance()->startLogServer("./log" ,"TestLog",true);

	CCsgServer::instance()->startMainLogicServer();

#ifdef _DEBUG
	CMemToolHelper::printTypeSize();
#endif

	start_main(argc ,argv);

	CCsgServer::instance()->stop();

	//cin.get();
	return 0;
}