#ifndef _TEST_LOG_TEST_LOG_H_
#define _TEST_LOG_TEST_LOG_H_


#include "framework/datetime/datetime.h"
#include "engine/thread/thread.h"
#include <iostream>
#include "framework/log/Log.h"
#include "framework/json/value.h"
#include "engine/baseServer/SocketServer.h"
#include "../TestDef.h"
#include "engine/baseServer/SocketClient.h"
#include "engine/net/session/sessionMgr.h"
#include "../../Message/TestStruct.h"
#include "../../Message/Test.h"
#include "../logic/ITestImpl.h"
#include <stdlib.h>
#include "framework/tool/debugTool.h"

using namespace csg;
using namespace Message;

void testDateTime()
{
	for ( int i = 0; i < 15; i++ )
	{
		std::cout << "now is " << CDateTime().asString() << std::endl;
		CThread::sleep_for(1000);
	}
}

void testLog()
{
	for ( int i = 0; i < 15; i++ )
	{
		LogDebug("for log now is " << CDateTime().asString());
		CThread::sleep_for(1000);
	}
}

void startSrv()
{
	CSocketServer srv;
	srv.init(test_royalchen_port ,false ,ESessionTypeClient);
	srv.startListen();
	onlyQForExit();
// 	CSessionMgr::instance()->disconnectAll();
// 	srv.stop();
}

void startSrvEx() {
	boost::shared_ptr<CSocketServer> srv(new CSocketServer());
	srv->init(test_royalchen_port, false, ESessionTypeClient);
	srv->startListen();
	onlyQForExit();
}

void startClientRemote()
{
	boost_CSocketClient_ptr client(new CSocketClient());
	//client->init(test_royalchen_url ,test_royalchen_port ,false);
	client->init(localhost_url, test_royalchen_port, false);
	client->startConnect();

	LogDebug("only q will exit,watting.....");
	STestStruct_Ptr t=new STestStruct();
	t->a = 35356;
	t->b = 342423;
	t->ib.push_back(3);
	t->ib.push_back(5);
	t->str = "good,nice";

	CMsgBlockPtr mb = new CMsgBlock();
	mb->_msgHead.command = 988;
	mb->_msgHead.fromId.id = 1992;
	mb->_msgBase = t;

	STestMap_Ptr tm = new STestMap();
	tm->a = 99;
	tm->ii[5] = 35;
	tm->ii[6] = 36;
	tm->il[1] = 1.95;
	tm->il[2] = 9.474;
	tm->ss["hihi"] = "good";
	tm->ss["oo"] = "gwgwe";
	tm->iff[8967] = 6.4888;
	tm->iff[798] = 876.466;

	STest_Ptr tp = new STest();
	tp->a = 4644;
	tp->tt.a = 2432;
	tp->tt.ib.push_back(555);


	csg_proxy::ITest trpc;
	do
	{
		std::string inputStr;
		getline(std::cin ,inputStr);
		if ( "b" == inputStr )
		{
			break;
		} else if ( "c" == inputStr )
		{
			mb->_msgBase = t;
			client->pushMessage(mb);
		}
		else if ("e" == inputStr) {
			mb->_msgBase = tm;
			client->pushMessage(mb);
		}
		else if ("t"==inputStr) {
			mb->_msgBase = tp;
			client->pushMessage(mb);
		}
		else if ("r" == inputStr) {
			LogDebug("start rpc test");			
			CCli_ITest_t3_CallBackPtr cb = new CCli_ITest_t3_CallBack();
			trpc.t3_async(client->getSession(), cb, 2523, "oojigwoeg");
		}
	} while ( true );

	onlyQForExit();


}

void startClientLocal()
{
	boost_CSocketClient_ptr client(new CSocketClient());
	//client->init(test_royalchen_url, test_royalchen_port, false);
	client->init(localhost_url, test_royalchen_port, false);
	client->startConnect();

	LogDebug("only q will exit,watting.....");
	STestStruct_Ptr t = new STestStruct();
	t->a = 35356;
	t->b = 342423;
	t->ib.push_back(3);
	t->ib.push_back(5);
	t->str = "good,nice";

	CMsgBlockPtr mb = new CMsgBlock();
	mb->_msgHead.command = 988;
	mb->_msgHead.fromId.id = 1992;
	mb->_msgBase = t;


	csg_proxy::ITest trpc;
	do
	{
		std::string inputStr;
		getline(std::cin, inputStr);
		if ("b" == inputStr)
		{
			break;
		}
		else if ("c" == inputStr)
		{
			client->pushMessage(mb);
		}
		else if ("r" == inputStr) {
			LogDebug("start rpc test");
			CCli_ITest_t3_CallBackPtr cb = new CCli_ITest_t3_CallBack();
			trpc.t3_async(client->getSession(), cb, 2523, "oojigwoeg");
		}
	} while (true);

	onlyQForExit();


}


void startClientLocalLoop()
{
	boost_CSocketClient_ptr client(new CSocketClient());
	//client->init(test_royalchen_url, test_royalchen_port, false);
	client->init(localhost_url, test_royalchen_port, false);
	client->startConnect();

	CThread::sleep_for(2000);

	LogDebug("only q will exit,watting.....");
	STestStruct_Ptr t = new STestStruct();
	t->a = 35356;
	t->b = 342423;
	t->ib.push_back(3);
	t->ib.push_back(5);
	t->str = "good,nice";

	CMsgBlockPtr mb = new CMsgBlock();
	mb->_msgHead.command = 988;
	mb->_msgHead.fromId.id = 1992;
	mb->_msgBase = t;


	csg_proxy::ITest trpc;
	do
	{
		int num = rand() % 2;
		if (0 == num) {
			client->pushMessage(mb);
		}
		else {
			LogDebug("start rpc test");
			CCli_ITest_t3_CallBackPtr cb = new CCli_ITest_t3_CallBack();
			trpc.t3_async(client->getSession(), cb, 2523, "oojigwoeg");
		}
		CThread::sleep_for(200);
	} while (true);

	onlyQForExit();


}


void testAsio(Json::Value& js)
{
	int type = js[1].asInt();
	switch ( type )
	{
		case 1:
		{
			startSrv();
		}
		break;
		case 2:
		{
			startClientRemote();
		}
		break;
		case 3:
		{
			startSrvEx();
		}
		break;
		case 4: 
		{
			CCsgServer::instance()->startListenServer(test_royalchen_port, false, ESessionTypeClient);
		}
		break;
		case 5:
		{
			startClientLocal();
		}
		break;
		case 6: {
			startClientLocalLoop();
		}
		break;
	}
}



void testStackBrace() {
	std::string callInfo;
	csg::CDebugToolManager::instance()->getCurrentStack(callInfo);
	LogDebug("test stack info:" << callInfo);
}

void testMemInfo() {
	std::string memInfo;
	csg::CDebugToolManager::instance()->getCurrentMemInfo(memInfo);
	LogDebug("test meminfo:" << memInfo);
}


#endif