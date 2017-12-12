#ifndef _TEST_TEST_MAIN_H_
#define _TEST_TEST_MAIN_H_

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


void startMain()
{
	std::cout << "Program run in below environment !!!" << std::endl;
#ifdef _DEBUG
	std::cout << "_DEBUG set" << std::endl;
#endif

#ifdef CSG_WIN
	std::cout << "CSG_WIN set" << std::endl;
#endif

#ifdef CSG_LINUX
	std::cout << "CSG_LINUX set" << std::endl;
#endif

	//启动时间更新线程
	CThreadManager::instance()->activeBaseServer(EBaseServerUpdateDt);
	//log线程
	std::string dir = "TestApp";
	CThreadManager::instance()->activeBaseServer(EBaseServerLoggerWritter ,dir);
	//启动网络IOCP
	if ( -1 == CSocketManager::instance()->init() )
	{
		std::cout << "socket init fail" << std::endl;
		cin.get();
		return ;
	}

	testSerializeEx();

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

	char ch;
	//std::cout << "enter b for exit!" << std::endl;
	std::cout << "enter anykey for exit!" << std::endl;
	do
	{
		ch = cin.get();
		// 		if ( 'b' == ch )
		// 			break;
		break;
		CThread::sleep_for(100);
	} while ( true );

	CThreadManager::instance()->killAllTask();

	//等待所有线程执行退出完成
	CThread::sleep_for(2000);
}


int main(int argc, char** argv){
	
	try
	{
		startMain();
	} catch ( exception &ex )
	{
		std::cerr << "exception ,code=" << ex.what() << std::endl;
	}

	return 0;
}

#endif