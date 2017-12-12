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


int main(int argc, char** argv){

	int k = 0;
	std::cout << "hello,next is your code run result"<<std::endl;

	//启动时间更新线程
	CThreadManager::instance()->activeBaseServer(EBaseServerUpdateDt);
	//log线程
	std::string dir = "TestApp";
	CThreadManager::instance()->activeBaseServer(EBaseServerLoggerWritter,dir);

	//testCounter(5);

	//testSerialize();

	//testTime();

	//testThread();

	testLog();

	char ch;
	std::cout << "enter b for exit!" << std::endl;
	do
	{
		ch = cin.get();
		if ( 'b' == ch )
			break;
		CThread::sleep_for(100);
	} while ( true );

	CThreadManager::instance()->killAllTask();

	//等待所有线程执行退出完成
	CThread::sleep_for(1000);

	return 0;
}

#endif