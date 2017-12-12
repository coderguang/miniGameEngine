
#ifndef _TEST_CMD_MANAGER_H_
#define _TEST_CMD_MANAGER_H_

#include "framework/json/value.h"
#include <iostream>
#include "framework/util/CCmdManager.h"
#include "TestBoost.h"
#include "TestAsio.h"
#include "TestUtil.h"
#include "TestAsioEx.h"

void testCmdA(Json::Value& js)
{
	std::cout << "hi,cmdA" << std::endl;
}
void testCmdB(Json::Value& js)
{
	std::cout << "hi,cmdB" << std::endl;
}
void testCmdC(Json::Value& js)
{
	std::cout << "hi,cmdC" << std::endl;
}


void registCmd()
{
	//testAsioEx();

	//testAsioHook();

	//return; //hook test

// 	CCmdManager::instance()->registCmd("cmdA" ,"testA" ,testCmdA);
// 	CCmdManager::instance()->registCmd("cmdB" ,"testB" ,testCmdB);
// 	CCmdManager::instance()->registCmd("cmdC" ,"testC" ,testCmdC);
// 	CCmdManager::instance()->registCmd("cmdA" ,"testC" ,testCmdC);

	//boost timer
	CCmdManager::instance()->registCmd("t_b_tr" ,"test boost timer" ,testBoostTimer);
	CCmdManager::instance()->registCmd("t_b_tr_a" ,"test async_boost timer" ,testBoostAsyncTimer);
	CCmdManager::instance()->registCmd("t_b_tr_ab", "test async_boost timer by other thread run io_service", testBoostTimerByOtherThread);
	// static member desconstructor
	CCmdManager::instance()->registCmd("t_s_md" ,"test static desconstructor by static member" ,testStaticDesconstructorWithStatic);
	CCmdManager::instance()->registCmd("t_s_mdn" ,"test static desconstructor by not static member" ,testStaticDesconstructorNotStatic);

	CCmdManager::instance()->registCmd("t_asio" ,"test asio£¬0 for srv,1 for cli" ,testAsio);

	CCmdManager::instance()->registCmd("a" ,"test asioex£¬0 for srv,1 for cli" ,testAsioEx);
}


#endif
