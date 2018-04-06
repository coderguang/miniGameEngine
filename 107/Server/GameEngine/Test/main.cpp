#include <iostream>
#include "engine/core/csgServer.h"
#include "TestCmdManager.h"
#include "log/TestLog.h"
#include "framework/util/CCmdManager.h"
#include "lua/testLua.h"

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


void start_lua() {

	lua_State *L = luaL_newstate();

	luaL_openlibs(L);

	luaL_dofile(L, "../LuaScript/Main.lua");
	//luaL_dofile(L, "../../LuaScript/Main.lua");

	lua_close(L);

	LogDebug("start lua ok");
	return;

}


int main(int argc ,char **argv)
{

// 	start_lua();
// 	start_main(argc ,argv);
// 	onlyQForExit();
// 	return 0;

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

	start_main(argc ,argv);

	CCsgServer::instance()->stop();

	cin.get();
	return 0;
}