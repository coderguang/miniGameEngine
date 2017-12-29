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

using namespace csg;

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
}
void startClient()
{
	CSocketClient client;
	client.init(localhost_url ,test_royalchen_port ,false);
	client.startConnect();

	LogDebug("only q will exit,watting.....");
	do
	{
		std::string inputStr;
		getline(std::cin ,inputStr);
		if ( "b" == inputStr )
		{
			break;
		} else if ( "c" == inputStr )
		{
			client.testWrite();
		}
	} while ( true );

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
			startClient();
		}
		break;
	}
}


#endif