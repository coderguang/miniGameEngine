#ifndef _TEST_TEST_MAIN_H_
#define _TEST_TEST_MAIN_H_
//一定要第一个include asio.hpp，否则后面很容易和其他windows文件冲突
#include <boost/asio.hpp>

#include "framework/counter/counterHandler.h"
#include "engine/def/csg_def.h"
#include "engine/serialize/serializestream.h"
#include "TestSerialize.h"
#include "TestThread.h"


#include <iostream>
#include "TestTime.h"
#include "TestLog.h"
#include "TestSmartPtr.h"
#include "TestSocket.h"
#include "TestBaseWinSocket.h"
#include "framework/log/Log.h"
#include "TestUtil.h"
#include "TestChat.h"
#include "engine/net/socket/socketManager.h"
#include <exception>
#include "TestSerializeEx.h"
#include "TestRpc.h"
#include "TestTimer.h"
#include "framework/counter/counterHandlerManager.h"
#include "TestMongo.h"
#include "TestCmdManager.h"
#include "framework/util/CCmdManager.h"

void startMain()
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
	/*
	long64_t t = 3124124235423;
	double d = 0.254;
	bool b = false;
	short s = 135;
	LogDebug("test log t=" << t << ",d=" << d<<" b="<<b<<",s="<<s);
	*/
	//启动时间更新线程
	CThreadManager::instance()->activeBaseServer(EBaseServerUpdateDt);
	//log线程
	std::string dir = "TestApp";
	CThreadManager::instance()->activeBaseServer(EBaseServerLoggerWritter ,dir);

	CThreadManager::instance()->activeBaseServer(EBaseServerMainLogic);

	//启动网络IO发送线程
	CThreadManager::instance()->activeBaseServer(EBaseServerSocketSend);

	//启动网络IOCP
	if ( -1 == CSocketManager::instance()->init() )
	{
		LogDebug("socket init fail");
		cin.get();
		return;
	}


	//监控对象数量
	CCounterHandlerManager::initPrintCounterTimer();

	//testMongo();

	//testTimer();

	//testRPC();

	//testSerializeEx();

	//testCounter(5);

	//testSerialize();

	//testTime();

	//testThread();

	//testLog();

#ifdef CSG_WIN
	//testSocket();

	//testBaseWinSocket();

	//testChat();

	//testSmartPtr();
#endif

#ifdef CSG_LINUX
	//testSmartPtr();
#endif

	//testUtil();
	//#ifdef CSG_WIN
	//testChat();
	//#endif

	//#ifdef CSG_LINUX
	//testLinuxChat();
	// #endif

	/*
	char ch;
	//std::cout << "enter b for exit!" << std::endl;
	LogDebug("enter anykey for exit!");
	do
	{
		ch = cin.get();
		// 		if ( 'b' == ch )
		// 			break;
		break;
		CThread::sleep_for(100);
	} while ( true );
	*/

	LogInfo("start regist cmd ...");
	registCmd();
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
			LogErr("startMain deal cmd occure exception,ex = " << ex.what());
		} catch ( ... )
		{
				LogErr("startMain deal cmd occure exception unknow exception");
		}

	} while ( true );
	



	CThreadManager::instance()->killAllTask();

	//等待所有线程执行退出完成
	CThread::sleep_for(2000);
}


void startSimpleMain()
{
	LogDebug("start simple model");

	//启动时间更新线程
	CThreadManager::instance()->activeBaseServer(EBaseServerUpdateDt);
	//log线程
	std::string dir = "TestApp";
	CThreadManager::instance()->activeBaseServer(EBaseServerLoggerWritter ,dir);

	LogInfo("start regist cmd ...");
	registCmd();

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
			LogErr("startSimpleMain deal cmd occure exception,ex="<< ex.what());
		} catch ( ... )
		{
			LogErr("startSimpleMain deal cmd occure exception unknow exception");
		}

	} while ( true );

}

int main(int argc, char** argv){
	
	try
	{
		//startMain();
		startSimpleMain();
	} catch ( std::exception &ex )
	{
		std::cerr << "exception ,code=" << ex.what() << std::endl;
	}

	return 0;
}

#endif