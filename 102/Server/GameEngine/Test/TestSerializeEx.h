#include "../Message/GameMsg.h"
#include "TestSerialize.h"
#include "../../Engine/engine/thread/thread.h"
#ifndef _TEST_TEST_SERIALIZE_EX_H_
#define _TEST_TEST_SERIALIZE_EX_H_

using namespace csg;
using namespace Message;
void testSend()
{
	//std::string host = "123.207.87.135";
	std::string host = "127.0.0.1";

	int socketfd = CSocketHelper::getClientSocket(AF_INET ,SOCK_STREAM ,0 ,DefaultPort ,host);
	if ( -1 == socketfd )
	{
		CSG_LOG_DEBUG("testSend get socket fail");
		return;
	}

	char ch;
	while ( true )
	{
		ch = cin.get();
		if ( 'b' == ch )
		{
			break;
		}

		SeriaInt msg;
		msg.aInt = rand() % 1000;
		msg.print();

		CSerializeStream srcOS;
		srcOS.setUseBitMark(true);
		msg.write(srcOS);
		srcOS.prepareToAppend();

		CSerializeStream tmpOS;
		tmpOS.writeSize(srcOS.getFlagDataSize());
		tmpOS.append(srcOS.getFlagData() ,srcOS.getFlagDataSize());
		tmpOS.append(srcOS.getData() ,srcOS.getDataSize());

		int sendSize = CSocketHelper::sendMsg(socketfd ,tmpOS.getData() ,tmpOS.getDataSize());
		CSG_LOG_DEBUG("send size="<<ToStr(sendSize));
	}

}

void testRecv()
{
	CSocketManager::instance()->startListen(AF_INET ,SOCK_STREAM ,0 ,DefaultPort);
	std::cout << "listen start" << std::endl;
	cin.get();
	cin.get();
}

void testSendAll()
{
	std::string host = "123.207.87.135";
	//std::string host = "127.0.0.1";

	int socketfd = CSocketHelper::getClientSocket(AF_INET ,SOCK_STREAM ,0 ,DefaultPort ,host);
	if ( -1 == socketfd )
	{
		CSG_LOG_DEBUG("testSend get socket fail");
		return;
	}

	char ch;
	while ( true )
	{
//		ch = cin.get();
// 		if ( 'b' == ch )
// 		{
// 			break;
// 		}

		SeriaTestAllTest msg;
		msg.randValue();
		msg.print();

		CSerializeStream srcOS;
		srcOS.setUseBitMark(true);
		msg.write(srcOS);
		srcOS.prepareToAppend();

		CSerializeStream tmpOS;
		tmpOS.writeSize(srcOS.getFlagDataSize());
		tmpOS.append(srcOS.getFlagData() ,srcOS.getFlagDataSize());
		tmpOS.append(srcOS.getData() ,srcOS.getDataSize());

		int sendSize = CSocketHelper::sendMsg(socketfd ,tmpOS.getData() ,tmpOS.getDataSize());

		CSG_LOG_DEBUG("send size=" << ToStr(sendSize));

		CThread::sleep_for(1000);
	}
}

void testSerializeEx()
{
	char ch;
	do
	{
		std::cout << "enter s fro server,c fro client,other for nothing" << std::endl;
		ch = cin.get();
		if ( 's' == ch )
		{
			testRecv();
			break;
		} else if ( 'c' == ch )
		{
			testSendAll();
			//testSend();
		}
	} while ( true );
}

#endif