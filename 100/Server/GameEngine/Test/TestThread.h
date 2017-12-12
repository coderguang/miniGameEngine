
#ifndef _TEST_TEST_THREAD_H_
#define _TEST_TEST_THREAD_H_

#include <thread>
#include "framework/counter/counterHandler.h"
#include "framework/log/Log.h"
#include <thread>
#include "framework/io/PrintIOHandler.h"

using namespace csg;

void printObject(int v)
{
	static int counter = 0;
	for ( int i = 0; i < v; i++ )
	{
		counter++;
		std::cout << ",count=" << counter << std::endl;
	}
	/*
	static CCounterHandler t("test");
	CPrintIOHandler* log = new CPrintIOHandler();
	t.print(log);
	*/
}

void testCounter(int num)
{
	CCounterHandler t("test");
	for ( int i = 0; i <= num; i++ )
	{
		std::cout << ",thread=" << i << std::endl;
		std::thread t2(printObject,100);
		t2.detach();
	}
}



#endif