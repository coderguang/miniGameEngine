#ifndef _TEST_ASIO_H_
#define _TEST_ASIO_H_

#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include "TestUtil.h"
#include "boost/asio/ip/tcp.hpp"
#include "boost/array.hpp"
#include "framework/log/Log.h"

static const int TEST_ASIO_PORT = 10000;
static std::string asio_ipAddr = "127.0.0.1";

void testAsioSrv() {
	using namespace boost::asio;
	io_service io_service; 
	ip::tcp::acceptor acceptor(io_service ,ip::tcp::endpoint(ip::tcp::v4() ,TEST_ASIO_PORT)); //创建acceptor
	ip::tcp::socket srv_socket(io_service);//socket绑定io_service

	LogInfo("testAsioSrv before accept");

	//acceptor.accept(srv_socket);//使用调度器等待连接

	
	acceptor.listen(10);

	LogInfo("testAsioSrv after accept");

	onlyQforExitFunc();
}

void testAsioClient()
{
	using namespace boost::asio;
	io_service io_service;
	ip::tcp::socket client_socket(io_service);
	ip::tcp::endpoint client_ep(ip::address::from_string(asio_ipAddr) ,TEST_ASIO_PORT);

	LogInfo("testAsioClient before connect...");

	io_service.run();

	boost::system::error_code ec;
	client_socket.connect(client_ep,ec);
	if ( ec )
	{
		LogInfo("testAsioClient err,code="<<ec.message());
	}

	LogInfo("testAsioClient after connect!");
}

void testOldClient()
{
	int socketfd = CSocketManager::instance()->startConnect(AF_INET ,SOCK_STREAM ,0 ,TEST_ASIO_PORT ,asio_ipAddr);
	if ( -1 == socketfd )
	{
		LogDebug("testSend get socket fail");
		return;
	}
	LogInfo("testOldClient after connect!");
}

void asioDtClient()
{
	try
	{
		using namespace boost;
		asio::io_service io_service;

		asio::ip::tcp::socket socket(io_service);
		asio::ip::address addr;
		addr.from_string("127.0.0.1");
		asio::ip::tcp::endpoint endpoint(addr,TEST_ASIO_PORT);

		system::error_code err;
		socket.connect(endpoint,err);

		if ( err )
		{
			LogInfo("recive srv message," << err.message());
			return;
		}

		for ( ;; )
		{
			boost::array<char ,128> buf;
			system::error_code error_code;
			size_t len = socket.read_some(boost::asio::buffer(buf) ,error_code);
			if ( error_code == asio::error::eof )
			{
				LogInfo("connection close");
			} else if ( error_code )
			{
				LogInfo("connection occer other error,code=" << error_code.message());
			}
			std::string str(buf.data() ,len);
			LogInfo("recive srv message," << str);
		}
	} catch (std::exception& ex)
	{
		LogInfo("recive srv message," <<ex.what());
	}
}


void asioDtSrv()
{
	using namespace boost;
	
	try
	{
		asio::io_service io_service;
		asio::ip::tcp::acceptor acceptor(io_service ,asio::ip::tcp::endpoint(asio::ip::tcp::v4() ,TEST_ASIO_PORT));

		for ( ;;)
		{
			asio::ip::tcp::socket socket(io_service);
			acceptor.accept(socket);

			std::string dtStr = CDateTime().asString();
			boost::system::error_code ignored_error;
			asio::write(socket ,asio::buffer(dtStr) ,ignored_error);
			LogErr("asioDtSrv,msg=" <<dtStr);
		}
	} catch ( std::exception& ex )
	{
		LogErr("asioDtSrv error,msg=" << ex.what());
	}
}

void testAsio1()
{
	boost::asio::io_service io_service;

	io_service.run();

	std::cout << "Do you reckon this line displays?" << std::endl; //can see
}
void testAsio2()
{

	boost::asio::io_service io_service;
	boost::asio::io_service::work work(io_service);

	io_service.run();

	std::cout << "Do you reckon this line displays?" << std::endl;  //can't see
}
void testAsio3()
{
	boost::asio::io_service io_service;

	for ( int x = 0; x < 42; ++x )
	{
		io_service.poll();
		std::cout << "Counter: " << x << std::endl;
	}
}

void testAsio4()
{
	boost::asio::io_service io_service;
	boost::asio::io_service::work work(io_service);

	for ( int x = 0; x < 42; ++x )
	{
		io_service.poll();
		std::cout << "Counter: " << x << std::endl;
	}
}

void testAsio5()
{
	boost::asio::io_service io_service;
	boost::shared_ptr< boost::asio::io_service::work > work(
		new boost::asio::io_service::work(io_service)
	);

	work.reset();

	io_service.run();

	LogDebug( "Do you reckon this line displays?");
}

boost::asio::io_service io_service6;
void asioWorkerThread()
{
	LogDebug("Thread Start\n");
	io_service6.run();
	LogDebug("Thread Finish\n");
}

void testAsio6()
{
	boost::shared_ptr< boost::asio::io_service::work > work(
		new boost::asio::io_service::work(io_service6)
	);

	LogDebug("Press [return] to exit.");

	boost::thread_group worker_threads;
	for ( int x = 0; x < 4; ++x )
	{
		worker_threads.create_thread(asioWorkerThread);
	}

	std::cin.get();

	io_service6.stop();

	worker_threads.join_all();

	return ;
}

void testBind()
{
	LogDebug("hello,bind");
	onlyQforExitFunc();
}

class testAsioClass
{
public:
	void F3(int i ,float f)
	{
		LogDebug( "i: " << i );
		LogDebug("f: " << f );
	}
};

void WorkerThreadEx(boost::shared_ptr< boost::asio::io_service > io_service)
{
	LogDebug( "Thread Start\n");
	io_service->run();
	LogDebug("Thread Finish\n");
}

void testAsio7()
{
	boost::shared_ptr< boost::asio::io_service > io_service(
		new boost::asio::io_service
	);
	boost::shared_ptr< boost::asio::io_service::work > work(
		new boost::asio::io_service::work(*io_service)
	);

	LogDebug("Press [return] to exit.");

	boost::thread_group worker_threads;
	for ( int x = 0; x < 4; ++x )
	{
		worker_threads.create_thread(boost::bind(&WorkerThreadEx ,io_service));
	}

	std::cin.get();

	io_service->stop();

	worker_threads.join_all();
}

boost::mutex global_stream_lock;

void WorkerThreadLock(boost::shared_ptr< boost::asio::io_service > io_service)
{
	global_stream_lock.lock();
	LogDebug("[" <<
		"] Thread Start");
	global_stream_lock.unlock();

	io_service->run();

	global_stream_lock.lock();
	LogDebug("["  <<"] Thread Finish");
	global_stream_lock.unlock();
}

size_t fib(size_t n)
{
	if ( n <= 1 )
	{
		return n;
	}
	boost::this_thread::sleep(
		boost::posix_time::milliseconds(1000)
	);
	return fib(n - 1) + fib(n - 2);
}

void CalculateFib(size_t n)
{
	global_stream_lock.lock();
	LogDebug("[""] Now calculating fib( " << ToStr(n) );
	global_stream_lock.unlock();

	size_t f = fib(n);

	global_stream_lock.lock();
	LogDebug("[" 
		<< "] fib( " <<ToStr( n )<< " ) = " << ToStr(f) );
	global_stream_lock.unlock();
}

void testAsio9()
{
	boost::shared_ptr< boost::asio::io_service > io_service(
		new boost::asio::io_service
	);
	boost::shared_ptr< boost::asio::io_service::work > work(
		new boost::asio::io_service::work(*io_service)
	);

	global_stream_lock.lock();
	LogDebug("["<< "] The program will exit when all work has finished.");
	global_stream_lock.unlock();

	boost::thread_group worker_threads;
	for ( int x = 0; x < 2; ++x )
	{
		worker_threads.create_thread(
			boost::bind(&WorkerThreadLock ,io_service)
		);
	}

	io_service->post(boost::bind(CalculateFib ,3));
	io_service->post(boost::bind(CalculateFib ,4));
	io_service->post(boost::bind(CalculateFib ,5));

	work.reset();

	worker_threads.join_all();
}


void testAsio8()
{
	boost::shared_ptr< boost::asio::io_service > io_service(
		new boost::asio::io_service
	);
	boost::shared_ptr< boost::asio::io_service::work > work(
		new boost::asio::io_service::work(*io_service)
	);

	global_stream_lock.lock();
	LogDebug("[" << "] Press [return] to exit." );
	global_stream_lock.unlock();

	boost::thread_group worker_threads;
	for ( int x = 0; x < 4; ++x )
	{
		worker_threads.create_thread(boost::bind(&WorkerThreadLock ,io_service));
	}

	std::cin.get();

	io_service->stop();

	worker_threads.join_all();
}


void testAsioSrv2() { 
	boost::asio::io_service io_service;
	boost::asio::ip::tcp::acceptor acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), TEST_ASIO_PORT));
	while (true) {
		boost::asio::ip::tcp::socket socket(io_service);
		acceptor.accept(socket);
		LogDebug("client=" << socket.remote_endpoint().address().to_string());
		boost::system::error_code err;
		socket.write_some(boost::asio::buffer("hello asio"), err);
		if (err) {
			LogDebug("error=" <<err.message());
			break;
		}
	}
	onlyQforExitFunc();
}
void testAsioClient2() {
	using namespace boost::asio;
	io_service iosev;
	ip::tcp::socket socket(iosev);
	ip::tcp::endpoint ep(ip::address_v4::from_string("123.207.87.135"), 8989);
	boost::system::error_code err;
	socket.connect(ep, err);
	if (err) {
		LogDebug("client error ,msg:" << err.message());
		return;
	}
	char buf[100];
	size_t len = socket.read_some(buffer(buf), err);
	std::string str(buf);
	LogDebug("recive buf " << str);

}

void testResolver()
{
	using namespace boost::asio;

	io_service iosev;
	ip::tcp::resolver resol(iosev);
	ip::tcp::resolver::query query("www.baidu.com" ,"http");
	ip::tcp::resolver::iterator iter = resol.resolve(query);
	ip::tcp::resolver::iterator end;
	while ( iter != end )
	{
		ip::tcp::endpoint enp = *iter++;
		LogDebug("ip=" << enp.address().to_string());
	}
	onlyQforExitFunc();
}


void testAsioHook()
{
	//testAsioSrvByResolver();

	//testResolver();
	//testAsio9();
	//testAsio8();
	//testAsio7();
	//testAsioClass t;
	//boost::bind(&testAsioClass::F3 ,&t ,4654 ,0.45)();
	//boost::bind(&testBind)();//main thread call testBind
	//testAsio6();
	//onlyQforExitFunc();
}

void testAsio(Json::Value& js)
{
	int type = js[1].asInt();
	
	switch (type )
	{
		case 9:
			testAsioSrv2();//can work
			break;
		case 10:
			testAsioClient2(); // can work
			break;
		case 7:
			testAsio3();
		break;
		case 8:
		testAsio4();
		break;
		default:
		break;
	}


	if ( 0 == type )
	{
		testAsioSrv();
	} else if ( 6 == type )
	{
		testAsio2();
	} else if ( 5 == type )
	{
		testAsio1();
	} else if ( 1 == type )
	{
		testAsioClient();
	} else if ( 2 == type )
	{
		testOldClient();
	} else if ( 3 == type )
	{
		asioDtSrv();
	} else if ( 4 == type )
	{
		asioDtClient();
	}

}


#endif