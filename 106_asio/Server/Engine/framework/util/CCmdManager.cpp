#include "framework/util/CCmdManager.h"
#include "../log/Log.h"
#include "../json/reader.h"
#include "engine/def/color_def.h"

void csg::CCmdManager::registCmd(std::string cmdKey ,std::string Desc ,dealFun func)
{
	if ( isCmdRegist(cmdKey) )
	{
		LogErr("CCmdManager::registCmd :cmd=" << cmdKey << " had regist");
		return;
	}
	CCmdStructPtr obj = new CCmdStruct();
	obj->cmd = cmdKey;
	obj->desc = Desc;
	obj->func = func;
	_map[cmdKey] = obj;
}

bool csg::CCmdManager::dealCmd(std::string& cmdStr)
{
	Json::Value params;
	try
	{
		Json::Reader reader;
		if ( !reader.parse(cmdStr.c_str() ,params) )
		{
			return false;
		}
	} catch ( ... )
	{
		LogErr("CCmdManager::dealCmd,cmdStr=" << cmdStr << " not a valid json array");
		return false;
	}
	if ( params.size() <= 0 || !params.isArray() )
	{
		LogErr("CCmdManager::dealCmd,cmdStr=" << cmdStr << " not a array or array size less than 1");
		return false;
	}
	std::string cmdKey = params[0].asString();

	MapCmdStruct::iterator it = _map.find(cmdKey);
	if ( it == _map.end() )
	{
		LogErr("CCmdManager::dealCmd,cmdKey=" << cmdKey << " not regist");
		return false;
	}
	try
	{
		it->second->func(params);
	} catch ( std::exception ex )
	{
		LogErr("deal cmd occure exception,key=" << cmdKey << ",ex=" << ex.what());
	} catch ( ... )
	{
		LogErr("deal cmd occure exception,key=" << cmdKey << "unknow exception");
	}
	return true;
}

void csg::CCmdManager::printCmd()
{
	CColorHelper::setColor(Color_Green);
	for ( MapCmdStruct::iterator it = _map.begin(); it != _map.end(); ++it )
	{
		std::cout << "[\"" << it->second->cmd << "\"]" << " :" << it->second->desc << std::endl;
	}
	std::cout << "q for exit the server......." << std::endl;
	CColorHelper::setColor(Color_White);
}

bool csg::CCmdManager::isCmdRegist(std::string& cmdKey)
{
	MapCmdStruct::iterator it = _map.find(cmdKey);
	if ( it != _map.end() )
	{
		return true;
	}
	return false;
}

