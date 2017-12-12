
#ifndef _TEST_TEST_BOOST_
#define _TEST_TEST_BOOST_

#include "framework/json/value.h"
#include "framework/log/Log.h"



#include <boost/asio.hpp>
//#include <boost/bind.hpp>
//#include <boost/function.hpp>
#include <boost/thread/thread.hpp>
#include "engine/thread/thread.h"


void testBoostPrint(const boost::system::error_code & ec){
	LogInfo("testBoostPrint is trigger");
}

void testBoostPrint2(const boost::system::error_code & ec){
	LogInfo("testBoostPrint2 is trigger");
}

void testBoostAsyncTimer(Json::Value& js){
	LogInfo("start test boost async timer");

	typedef boost::shared_ptr<boost::asio::io_service>			io_service_ptr;
	typedef boost::shared_ptr<boost::asio::io_service::work>	work_ptr;
	
	io_service_ptr io_serviceEx(new boost::asio::io_service);
	work_ptr work(new boost::asio::io_service::work(*io_serviceEx));

	boost::shared_ptr<boost::thread> thread(new boost::thread(
		boost::bind(&boost::asio::io_service::run,io_serviceEx)));

	LogInfo("start set timer");
	
	boost::asio::deadline_timer async_timer(*io_serviceEx);
	async_timer.expires_from_now(boost::posix_time::seconds(5));
	async_timer.async_wait(&testBoostPrint2);
	io_serviceEx->run();

	LogInfo("set timer end");
	


}



void testBoostTimer(Json::Value& js)
{
	LogInfo("start test boost timer");

	boost::asio::io_service io;
	boost::asio::deadline_timer timer(io ,boost::posix_time::seconds(5));

	timer.wait();
	LogInfo("sync timer run over");

	boost::asio::io_service io_async;
	boost::asio::deadline_timer at(io_async,boost::posix_time::seconds(5));

	//timer_callback callBack=[&]
	
	at.async_wait(&testBoostPrint);
	io_async.run();
	LogInfo("test async 1 boost timer over");


	boost::asio::io_service io_async2;
	boost::asio::deadline_timer at2(io_async2);
	at2.expires_from_now(boost::posix_time::seconds(8));

	//timer_callback callBack=[&]
	
	at2.async_wait(&testBoostPrint);
	io_async2.run();
	LogInfo("test async 2 boost timer over");
	
}


static boost::asio::io_service testTimerIoService;

void testBoostRunIo() {
	LogInfo("testBoostRunIo");
	testTimerIoService.run();
	LogInfo("testBoostRun ok");

}


void testBoostTimerByOtherThread(Json::Value& js) {
	
	LogInfo("testBoostTimerByOtherThread start");

	boost::asio::deadline_timer at(testTimerIoService, boost::posix_time::seconds(5));

	at.async_wait(&testBoostPrint);
	LogInfo("testBoostTimerByOtherThread async 1 boost timer over");

	boost::asio::deadline_timer at2(testTimerIoService);
	at2.expires_from_now(boost::posix_time::seconds(8));

	at2.async_wait(&testBoostPrint);

	LogInfo("testBoostTimerByOtherThread async 2 boost timer over");

	std::thread t(testBoostRunIo);
	t.detach();

	while (true)
	{
		LogInfo("enter q for exit this command");
		std::string inputStr;
		getline(std::cin ,inputStr);
		if ( "q" == inputStr )
		{
			break;
		}
	}

}



#endif
