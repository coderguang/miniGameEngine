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
#include "framework/tool/signalTool.h"
#include "framework/util/typetransform.h"

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


void sendMsgToSrv(boost_CSocketClient_ptr client, int sendType) {

	if (client->getSession()->getStatus() != ESessionStatusConnected)
		return;

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
	tm->msstring[STestStruct()] = "hiTesetStruct";

	STest_Ptr tp = new STest();
	tp->a = 4644;
	tp->tt.a = 2432;
	tp->tt.ib.push_back(555);


	csg_proxy::ITest trpc;


		
	if (1==sendType)
	{
		mb->_msgBase = t;
		client->pushMessage(mb);
	}
	else if (2==sendType) {
		mb->_msgBase = tm;
		client->pushMessage(mb);
	}
	else if (3 == sendType) {
		mb->_msgBase = tp;
		client->pushMessage(mb);
	}
	else if (4== sendType) {
		LogDebug("start rpc test t3");
		CCli_ITest_t3_CallBackPtr cb = new CCli_ITest_t3_CallBack();
		trpc.t3_async(client->getSession(), cb, 2523, "oojigwoeg");
		trpc.t3_async(client->getSession(), NULL, 2523, "oojigwoeg");
	}
	else if (5 == sendType) {
		LogDebug("start rpc test t4");
		CCli_ITest_t4_CallBackPtr cb = new CCli_ITest_t4_CallBack();
		Message::STestMap mm;
		mm.a = 12312;
		mm.ss["11"] = "242343";
		mm.ss["ge"] = "ges";
		STestStruct st;
		st.a = 99;
		st.ib.push_back(2432);
		mm.msstring[st] = "msstring";
		trpc.t4_async(client->getSession(), cb, mm);
	}
	else if (6 == sendType) {
		LogDebug("start rpc test t5");
		CCli_ITest_t5_CallBackPtr cb = new CCli_ITest_t5_CallBack();
		std::vector<STest> vt;
		for (int i = 0; i < 99; i++) {
			STest s;
			s.a = i;
			s.str = ToStr(i);
			vt.push_back(s);
		}
		trpc.t5_async(client->getSession(), cb, vt);
	}
	else if (7 == sendType) {
		LogDebug("start rpc test t6");
		CCli_ITest_t6_CallBackPtr cb = new CCli_ITest_t6_CallBack();
		std::map<std::string, STest> ms;
		for (int i = 0; i < 99; i++) {
			STest s;
			s.a = i;
			s.str = ToStr(i);
			ms[ToStr(i)] =s;
		}
		trpc.t6_async(client->getSession(), cb, ms);
	}
}


void sendMsgToSrvByOpt(boost_CSocketClient_ptr client) {
	do
	{
		std::string inputStr;
		getline(std::cin, inputStr);
		if ("1" == inputStr) {
			sendMsgToSrv(client, 1);
		}
		else if ("2" == inputStr) {
			sendMsgToSrv(client, 2);
		}
		else if ("3" == inputStr) {
			sendMsgToSrv(client, 3);
		}
		else if ("4" == inputStr) {
			sendMsgToSrv(client, 4);
		}
		else if ("5" == inputStr) {
			sendMsgToSrv(client, 5);
		}
		else if ("6" == inputStr) {
			sendMsgToSrv(client, 6);
		}
		else if ("7" == inputStr) {
			sendMsgToSrv(client, 7);
		}
		else if ("0" == inputStr)
			break;
	} while (true);

	onlyQForExit();
}

void startSendMsg(std::string url)
{
	boost_CSocketClient_ptr client(new CSocketClient());
	client->init(url ,test_royalchen_port ,false);
	client->startConnect();
	sendMsgToSrvByOpt(client);
}

void startSendLoop(std::string url)
{
	boost_CSocketClient_ptr client(new CSocketClient());
	client->init(url, test_royalchen_port, false);
	client->startConnect();

	do
	{

		if (client->getSession()->getStatus() != ESessionStatusConnected){
			continue;
			CThread::sleep_for(200);
		}

		int num = rand() % 10;

		sendMsgToSrv(client, num);
		CThread::sleep_for(200);
	} while (true);

	onlyQForExit();
}

void sendt6() {
	
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
			startSendMsg(localhost_url);
		}
		break;
		case 3:
		{
			startSrvEx();
		}
		break;
		case 4: 
		{
			CCsgServer::instance()->startListenServer(test_royalchen_port, true, ESessionTypeClient);
		}
		break;
		case 5:
		{
			startSendMsg(test_royalchen_url);
		}
		break;
		case 6: {
			startSendLoop(localhost_url);
		}
		break;
		case 7: {
			startSendLoop(test_royalchen_url);
		}
		break;
		case 8: //inner srv
		{
			CCsgServer::instance()->startListenServer(9201, true, ESessionTypeClient);
		}
		break;
		case 9:
		{
			boost_CSocketClient_ptr client(new CSocketClient());
			client->init(localhost_url, 9201, false);
			client->startConnect();
			sendMsgToSrvByOpt(client);
		}
		break;
		case 10: //websocket srv
		{
			CCsgServer::instance()->startListenServer(9201, false, ESessionTypeClient);
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

void testExceptionBrace(int k) {

	LogDebug(",k="<<k);
	throw csg::CException("test,tt");
}

void testCatchExcept() {

	try {
		int k=0;
		LogDebug("enter k value:");
		k<<std::cin.get();
		testExceptionBrace(k);
	}
	catch (...) {
		std::string callInfo;
		csg::CDebugToolManager::instance()->getCurrentStack(callInfo);
		LogDebug("exception stack info:" << callInfo);
	}
}

void testSignal() {
	
// 	signal(SIGINT, &csg::signalHandleExit);
// 	signal(SIGTERM, &csg::signalHandleKill);

	registSignalHandle();
}

void testSendString(Json::Value& js) {
	
	std::string msg = js[1].asString();
	LogDebug("start test msg:" << msg);
	boost_CSocketClient_ptr client(new CSocketClient());
	client->init(test_royalchen_url, test_royalchen_port, false);
	client->startConnect();

	Message::SScapyTest_Ptr t = new Message::SScapyTest();
	t->str = msg;

	CMsgBlockPtr mb = new CMsgBlock();
	mb->_msgHead.command = 988;
	mb->_msgHead.fromId.id = 1992;
	mb->_msgBase = t;
	int count = 0;
	do
	{
		if (client->getSession()->getStatus() != ESessionStatusConnected) {
			LogDebug("test msg:session not connected now:"<<count);
			count++;
			if (count >= 5)
			{
				LogDebug("test msg:session not connected now more than 5,return");
				return;
			}
		}
		else {
			client->pushMessage(mb);
			LogDebug("test msg:" << msg);
		}
		cin.get();\

	} while (true);
}

void testSendStringVm(Json::Value& js) {

	std::string msg = js[1].asString();
	LogDebug("start test msg:" << msg);
	boost_CSocketClient_ptr client(new CSocketClient());
	client->init(vm_url, test_royalchen_port, false);
	client->startConnect();

	Message::SScapyTest_Ptr t = new Message::SScapyTest();
	t->str = msg;

	CMsgBlockPtr mb = new CMsgBlock();
	mb->_msgHead.command = 988;
	mb->_msgHead.fromId.id = 1992;
	mb->_msgBase = t;
	int count = 0;
	do
	{
		if (client->getSession()->getStatus() != ESessionStatusConnected) {
			LogDebug("test msg:session not connected now:" << count);
			count++;
			if (count >= 5)
			{
				LogDebug("test msg:session not connected now more than 5,return");
				return;
			}
		}
		else {
			client->pushMessage(mb);
			LogDebug("test msg:" << msg);
		}
		cin.get(); \

	} while (true);
}


#endif