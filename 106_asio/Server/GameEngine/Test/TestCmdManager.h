#ifndef _TEST_TEST_CMD_MANAGER_H_
#define _TEST_TEST_CMD_MANAGER_H_

#include "framework/log/Log.h"
#include "log/TestLog.h"
#include "framework/util/CCmdManager.h"
#include "../Message/TestStruct.h"
#include "engine/rpc/rmiObjectAdapter.h"
#include "logic/ITestImpl.h"
#include "net/TestAsio.h"

using namespace csg;
using namespace Message;

void quickTest() {
	//startSrv();
	//startSrvEx();
}


void registStruct() {
	CTestStruct::regist();
}

void registImpl() {
	CRMIObjectAdapter::instance()->addRmiObject("Test", new ITestImpl());
}

void startRegistCmd()
{
	registImpl();
	quickTest();
	registStruct();
	LogDebug("start regist cmd........");
	CCmdManager::instance()->registCmd("a" ,"test asion net" ,testAsio);
	CCmdManager::instance()->registCmd("b", "test asio net ex", testAsioEx);

}

#endif