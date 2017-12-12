#ifndef _TEST_RPC_H_
#define _TEST_RPC_H_



#include "../Message/Test.h"
#include "engine/thread/thread.h"
#include "engine/rpc/rmiObjectAdapter.h"
#include "logic/ITestImpl.h"
#include "engine/rpc/rmiObject.h"
#include "framework/SmartPoint/smartPoint.h"
#include "engine/rpc/rpcHelper.h"
#include "framework/log/Log.h"
#include "framework/json/value.h"
#include "framework/json/reader.h"

void initRMIObject()
{
	CRMIObjectAdapter::instance()->addRmiObject("Test",new ITestImpl());
}

char getInput()
{
	char ch;
	do
	{
		ch = cin.get();
	} while ( ch == '\n' );
	return ch;
}


void testLinuxBuild()
{
	std::string host = "123.207.87.135";
	csg::SRMICall call;
	call.rpcId = 322;

	CAutoSerializeStream __os(CSerializeStreamPool::instance()->newObject());

	CRMIObjectBindPtr objectBind = NULL;

	//CRMI_Test_CallBackPtr callBack = new CRMI_Test_CallBack();

	int socketfd = CSocketManager::instance()->startConnect(AF_INET ,SOCK_STREAM ,0 ,DefaultPort ,host);
	if ( -1 == socketfd )
	{
		LogDebug("testSend get socket fail");
		return;
	}

	CSessionPtr session = new CSession(socketfd ,host ,DefaultPort ,false);

	//д��ص�
	//CRpcHelper::prepareToCall(session ,__os ,call ,callBack,objectBind);
}


void testRpcClient()
{
	//testLinuxBuild();
	std::string host1 = "127.0.0.1";
	std::string host2 = "123.207.87.135";

	char ch;
	std::string host;
	do
	{
		LogDebug("enter 1 for local host,2 for remote ");
		ch = getInput();
		if ( '1' == ch )
		{
			host = host1;
			break;
		} else if ( '2' == ch )
		{
			host = host2;
			break;
		}

	} while ( true );

	LogDebug("your select is "<<host);

	int socketfd = CSocketManager::instance()->startConnect(AF_INET ,SOCK_STREAM ,0 ,DefaultPort ,host);
	if ( -1 == socketfd )
	{
		LogDebug("testSend get socket fail");
		return;
	}

	CSessionPtr session = new CSession(socketfd ,host ,DefaultPort ,false);
	CProtocolPtr protocol = new CProtocol();
	session->setProtocol(protocol);
	session->setSocketfd(socketfd);

	CSessionManager::instance()->addSession(session);


	do
	{
		ch = getInput();
		LogDebug("enter c fro send,b for break,other for nothing");
		csg_proxy::ITest t;
		if ( 'v' == ch )
		{
			CCli_ITest_t3_CallBackPtr cb = new CCli_ITest_t3_CallBack();
			t.t3_async(session ,cb ,2523 ,"oojigwoeg");

		} else if ( 'c' == ch )
		{
			t.t2_async(session ,NULL,2222 ,"helooog");
		}
		else if ( 'b' == ch )
		{
			break;
		} else if ( 'm' == ch )
		{
			CMsgBlockPtr mb = new CMsgBlock();
			mb->_msgHead.command = 988;
			mb->_msgHead.fromId.id = 1992;

			Message::STest_Ptr test = new Message::STest();
			test->a = 1900;
			test->b = 2312;

			mb->_msgBase = test;

			CMsgQueue::instance()->pushMessage(session->getSocketfd() ,mb);
		}
		CThread::sleep_for(100);
	} while ( true );



}

void testSendData()
{
	std::string host1 = "127.0.0.1";
	std::string host2 = "123.207.87.135";

	char ch;
	std::string host;
	do
	{
		LogDebug("enter 1 for local host,2 for remote ");
		ch = getInput();
		if ( '1' == ch )
		{
			host = host1;
			break;
		} else if ( '2' == ch )
		{
			host = host2;
			break;
		}

	} while ( true );

	LogDebug("your select is " << host);

	int socketfd = CSocketManager::instance()->startConnect(AF_INET ,SOCK_STREAM ,0 ,DefaultPort ,host);
	if ( -1 == socketfd )
	{
		LogDebug("testSend get socket fail");
		return;
	}

	CSessionPtr session = new CSession(socketfd ,host ,DefaultPort ,false);
	CProtocolPtr protocol = new CProtocol();
	session->setProtocol(protocol);
	session->setSocketfd(socketfd);

	CSessionManager::instance()->addSession(session);

	do
	{
		ch = getInput();
		if ( 'v' == ch )
		{
			char buf[100] = "hello";
			int size=CSocketHelper::sendMsg(session->getSocketfd() ,buf ,sizeof(buf));
			LogDebug("send Data,sendSize="<<size<<",sizeof="<<(int)(sizeof(buf)));
		}
		CThread::sleep_for(100);
	} while ( true );



}


void testRpcRecv()
{
	initRMIObject();
	CSocketManager::instance()->startListen(AF_INET ,SOCK_STREAM ,0 ,DefaultPort);
	LogDebug("listen start");
	cin.get();
	cin.get();
}

void testJson()
{
	Json::Value js;
	js["hi"] = 1;
	js["hello"] = "hello";

	for ( int i = 0; i < 10; i++ )
	{
		js["array"].append(i);
	}


	std::string jsstr=js.toStyledString();

	LogDebug("js=" << jsstr);

	Json::Reader reader;
	
	Json::Value root;

	if ( reader.parse(jsstr ,root) )
		LogDebug("root=" << root.toStyledString());
}

void testRapidJson()
{
	// 1. �� JSON ������ DOM��
// 	const char* json = "{\"project\":\"rapidjson\",\"stars\":10}";
// 	RAPIDJSON_NAMESPACE::Document d;
// 	d.Parse(json);
// 	//LogDebug("d="<<d.GetString());
// 	// 2. ���� DOM �����޸ġ�
// 	RAPIDJSON_NAMESPACE::Value& s = d["stars"];
// 	s.SetInt(s.GetInt() + 1);
// 	//LogDebug("s=" << s.GetString());
// 	// 3. �� DOM ת����stringify���� JSON��
// 	RAPIDJSON_NAMESPACE::StringBuffer buffer;
// 	RAPIDJSON_NAMESPACE::Writer<RAPIDJSON_NAMESPACE::StringBuffer> writer(buffer);
// 	d.Accept(writer);
// 	// Output {"project":"rapidjson","stars":11}
// 	LogDebug("d="<<buffer.GetString());

}


void testRPC()
{
	testJson();
	//testRapidJson();
	Message::CTest::regist();
	char ch;
	do
	{
		LogDebug("enter s fro server,c fro client,other for nothing");
		ch = getInput();
		if ( 's' == ch )
		{
			LogDebug("start server");
			testRpcRecv();
			break;
		} else if ( 'c' == ch )
		{
			LogDebug("start client");
			testRpcClient();
			break;
		} else if ( 't' == ch )
		{
			LogDebug("start testSendData");
			testSendData();
			break;
		}
	} while ( true );

}


#endif