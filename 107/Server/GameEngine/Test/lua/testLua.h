#ifndef _TEST_LUA_TEST_LUA_H_
#define _TEST_LUA_TEST_LUA_H_

#include "framework/lua/lua.hpp"
#include "engine/def/environment_def.h"

using namespace csg;


static int average_lua(lua_State *L) {
	int n = lua_gettop(L);

	LogDebug("average_lua,param=" << n);

	double sum = 0;

	int i;

	for (i = 1; i <= n; i++) {
		sum += lua_tonumber(L, i);
	}

	lua_pushnumber(L, sum/n);

	return 2;
}

void testLuaFile() {
	lua_State* L = luaL_newstate();
	if (L == NULL) {
		LogErr("create lua state failed");
		return;
	}

	int bRet = luaL_loadfile(L, "hi.lua");

	if (bRet) {
		LogErr("load lua file error");
		return;
	}

	bRet = lua_pcall(L, 0, 0, 0);

	if (bRet) {
		LogErr("call lua file error");
		return;
	}
	
	lua_getglobal(L, "str");
	std::string str = lua_tostring(L, -1);

	LogDebug("get str=" << str);

	lua_getglobal(L, "tb1");

	lua_getfield(L, -1, "name");
	
	str = lua_tostring(L, -1);

	LogDebug("get name=" << str);



	lua_close(L);
}



void testLua() {
	//1.创建一个state  
	lua_State *L = luaL_newstate();

	//2.入栈操作  
	lua_pushstring(L, "I am so cool~,this is test lua");

	lua_pushnumber(L, 20);

	//3.取值操作  
	if (lua_isstring(L, 1)) {             //判断是否可以转为string  
		LogDebug(lua_tostring(L, 1));  //转为string并返回  
	}
	if (lua_isnumber(L, 2)) {
		LogDebug(lua_tonumber(L, 2));
	}

	//4.关闭state  
	lua_close(L);
	return;
}



void start_lua() {
	testLuaFile();
	//testLua();
}


#endif