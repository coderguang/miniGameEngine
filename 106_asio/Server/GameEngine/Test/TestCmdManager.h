#ifndef _TEST_TEST_CMD_MANAGER_H_
#define _TEST_TEST_CMD_MANAGER_H_

#include "framework/log/Log.h"
#include "log/TestLog.h"
#include "framework/util/CCmdManager.h"
#include "../Message/TestStruct.h"
#include "engine/rpc/rmiObjectAdapter.h"
#include "logic/ITestImpl.h"
#include "net/TestAsio.h"
#include "framework/tool/debugTool.h"
#include <string>
#include "framework/timer/timer.h"
#include "framework/timer/timerManager.h"

using namespace csg;
using namespace Message;

void quickTest() {
	//startSrv();
	//startSrvEx();
	// 	csg::CDebugToolManager::instance()->setShowCallStack(true);
	// 	csg::CDebugToolManager::instance()->setShowMemSize(true);
	// 	testStackBrace();
	// 	initMemTimer();
	//testCatchExcept();
	//testSignal();
}


void registStruct() {
	CTest::regist();
	CTestStruct::regist();
}

void registImpl() {
	CRMIObjectAdapter::instance()->addRmiObject("Test", new ITestImpl());
	CRMIObjectAdapter::instance()->addRmiObject("TestEx", new ITestImpl());
}

class CPrintMemTimer :public csg::CTimerBase {
public:
	CPrintMemTimer():CTimerBase("CPrintMemTimer"){
	
	}

	virtual int handleTimeOut(CDateTime& current) {
		testMemInfo();
		return 0;
	}
};

typedef csg::CSmartPointShare<CPrintMemTimer> CPrintMemTimerPtr;

void initMemTimer() {
	CPrintMemTimerPtr timer = new CPrintMemTimer();
	CTimerManager::instance()->addTimer(timer, CDateTime(), CInterval(5, 0));
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