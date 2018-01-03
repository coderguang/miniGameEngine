#ifndef _TEST_TEST_CMD_MANAGER_H_
#define _TEST_TEST_CMD_MANAGER_H_

#include "framework/log/Log.h"
#include "log/TestLog.h"
#include "framework/util/CCmdManager.h"

using namespace csg;

void quickTest() {
	//startSrv();
	//startSrvEx();
}

void startRegistCmd()
{
	quickTest();
	LogDebug("start regist cmd........");
	CCmdManager::instance()->registCmd("a" ,"test asion net" ,testAsio);

}

#endif