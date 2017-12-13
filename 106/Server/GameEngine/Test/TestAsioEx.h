
#ifndef _TEST_ASIO_EX_H_
#define _TEST_ASIO_EX_H_

#include "boost/system/error_code.hpp"
#include "boost/asio/io_service.hpp"
#include "boost/asio/ip/tcp.hpp"
#include "boost/asio/connect.hpp"
#include "TestUtil.h"
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include "boost/asio/placeholders.hpp"
#include "framework/log/Log.h"
#include <string>


static const std::string localhostip = "127.0.0.1";
static const std::string localhostport = "8989";

typedef boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr;
typedef boost::shared_ptr<boost::thread> thread_ptr;
typedef boost::shared_ptr<boost::asio::io_service> io_service_ptr;
typedef boost::shared_ptr<boost::asio::ip::tcp::acceptor> acceptor_ptr;
typedef boost::shared_ptr<boost::asio::io_service::work> work_ptr;

class myAsioTest
{
public:
	myAsioTest() 
	{
		io_service = io_service_ptr(new boost::asio::io_service);
		work = work_ptr(new boost::asio::io_service::work(*io_service));
		acceptor = acceptor_ptr(new boost::asio::ip::tcp::acceptor(*io_service ,boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4() ,8989)));
	};

	void start_connect()
	{
		using namespace boost::asio;

		ip::tcp::resolver resolver(*io_service);
		ip::tcp::resolver::query query(localhostip ,localhostport);
		ip::tcp::resolver::iterator iter = resolver.resolve(query);

		socket_ptr socketEx(new boost::asio::ip::tcp::socket(*io_service));
		boost::asio::async_connect(*socketEx ,iter ,boost::bind(&myAsioTest::handleConnect ,this,socketEx,boost::asio::placeholders::error));

	}

	
	void start_connect_remote()
	{
		using namespace boost::asio;

		ip::tcp::resolver resolver(*io_service);
		ip::tcp::resolver::query query("119.29.137.106" ,localhostport);
		ip::tcp::resolver::iterator iter = resolver.resolve(query);
		socket_ptr socketEx(new boost::asio::ip::tcp::socket(*io_service));
		boost::asio::async_connect(*socketEx ,iter ,boost::bind(&myAsioTest::handleConnect ,this ,socketEx ,boost::asio::placeholders::error));

	}
	
	void start_accept()
	{
		socket_ptr socketEx(new boost::asio::ip::tcp::socket(*io_service));
		acceptor->async_accept(*socketEx ,boost::bind(&myAsioTest::handle_accept ,this,socketEx,boost::asio::placeholders::error));
	}
	void run()
	{
		thread_ptr t(new boost::thread(boost::bind(&boost::asio::io_service::run ,io_service)));
		threads.push_back(t);
	}
	
	void start_read(socket_ptr socket)
	{
		socket->non_blocking(true);
		socket->async_read_some(boost::asio::null_buffers() ,boost::bind(
			&myAsioTest::handle_read ,this,socket ,boost::asio::placeholders::error ,boost::asio::placeholders::bytes_transferred));
	}

protected:

	void handle_read(socket_ptr socket,boost::system::error_code error ,size_t bytes_transferred)
	{
		if ( error )
		{
			LogErr("handle_read error,msg=" << error.message());
			socket->close();
			return;
		}
		boost::system::error_code read_err;

		const int read_len = 100;
		char buf[read_len];
		int len = socket->read_some(boost::asio::buffer(buf,28) ,read_err);
		buf[len - 1]= '\0';
		if (read_err) {
			LogErr("handle_read error read error,msg=" << read_err.message());
			socket->close();
			return;
		} else
		{
			std::string bufstr(buf);
			LogDebug("handle_read,msg=" << bufstr);
		}
		start_read(socket);
	}
	
	void handle_accept(socket_ptr socket ,const boost::system::error_code& error)
	{
		LogDebug("myAsioTest accept...");
		if ( !error )
		{
			std:string ip = "";
			try
			{
				ip = socket->remote_endpoint().address().to_string();
				LogDebug("myAsioTest accept...,ip=" << ip);
			} catch ( std::exception& ex )
			{
				LogDebug("myAsioTest accept...,ex=" << ex.what());
			}
			start_read(socket);
			start_accept();
		} else
		{
			LogDebug("myAsioTest accept...,err=" << error.message() << ",code=" << error.value());
			start_accept();
		}
	}
	
	void handleConnect(socket_ptr socketEx ,boost::system::error_code ex)
	{
		if ( ex )
		{
			LogErr("handle connect,ex=" << ex.message());
		} else
		{
			LogDebug("myAsioTest connect...");
			socketEx->async_write_some(boost::asio::null_buffers() ,boost::bind(&myAsioTest::handleWrite ,this ,socketEx ,boost::asio::placeholders::error));
		}
	}
	
	void handleWrite(socket_ptr socketEx ,boost::system::error_code err)
	{
		if ( err )
		{
			LogErr("handleWritet,ex=" << err.message());
			return;
		} else
		{
			LogDebug("handleWritet.....");
			boost::system::error_code write_err;
			std::string str = "hello,boost asio!are you ok?";
			int wlen=socketEx->write_some(boost::asio::buffer(str.c_str(),str.length()) ,write_err);
			if ( write_err )
			{
				LogErr("handleWritet write some,ex=" << write_err.message());
				return;
			} else
			{
				LogDebug("handleWritet write some,complete size=" << wlen);
			}
			CThread::sleep_for(5000);
			socketEx->async_write_some(boost::asio::null_buffers() ,boost::bind(&myAsioTest::handleWrite ,this ,socketEx ,boost::asio::placeholders::error));
		}

	}
	
private:
	io_service_ptr io_service;
	work_ptr work;
	acceptor_ptr acceptor;
	std::vector<thread_ptr> threads;
};


class myAsioTestClient{
public:
	myAsioTestClient()
	{
		io_service = io_service_ptr(new boost::asio::io_service);
		work = work_ptr(new boost::asio::io_service::work(*io_service));
		//作为客户端时，不要创建acceptor(与listen相同的端口),linux下回报错
	};

	void start_connect()
	{
		using namespace boost::asio;

		ip::tcp::resolver resolver(*io_service);
		ip::tcp::resolver::query query(localhostip ,localhostport);
		ip::tcp::resolver::iterator iter = resolver.resolve(query);

		socket_ptr socketEx(new boost::asio::ip::tcp::socket(*io_service));
		boost::asio::async_connect(*socketEx ,iter ,boost::bind(&myAsioTestClient::handleConnect ,this ,socketEx ,boost::asio::placeholders::error));

	}


	void start_connect_remote()
	{
		using namespace boost::asio;

		ip::tcp::resolver resolver(*io_service);
		ip::tcp::resolver::query query("test.royalchen.com" ,localhostport);
		ip::tcp::resolver::iterator iter = resolver.resolve(query);
		socket_ptr socketEx(new boost::asio::ip::tcp::socket(*io_service));
		boost::asio::async_connect(*socketEx ,iter ,boost::bind(&myAsioTestClient::handleConnect ,this ,socketEx ,boost::asio::placeholders::error));

	}
	void run()
	{
		thread_ptr t(new boost::thread(boost::bind(&boost::asio::io_service::run ,io_service)));
		threads.push_back(t);
	}

	void start_read(socket_ptr socket)
	{
		socket->non_blocking(true);
		socket->async_read_some(boost::asio::null_buffers() ,boost::bind(
			&myAsioTestClient::handle_read ,this ,socket ,boost::asio::placeholders::error ,boost::asio::placeholders::bytes_transferred));
	}

protected:

	void handle_read(socket_ptr socket ,boost::system::error_code error ,size_t bytes_transferred)
	{
		if ( error )
		{
			LogErr("myAsioTestClient handle_read error,msg=" << error.message());
			socket->close();
			return;
		}
		boost::system::error_code read_err;

		const int read_len = 100;
		char buf[read_len];
		int len = socket->read_some(boost::asio::buffer(buf ,28) ,read_err);
		buf[len - 1] = '\0';
		if ( read_err )
		{
			LogErr("myAsioTestClient handle_read error read error,msg=" << read_err.message());
			socket->close();
			return;
		} else
		{
			std::string bufstr(buf);
			LogDebug("myAsioTestClient handle_read,msg=" << bufstr);
		}
		start_read(socket);
	}

	void handleConnect(socket_ptr socketEx ,boost::system::error_code ex)
	{
		if ( ex )
		{
			LogErr("myAsioTestClient handle connect,ex=" << ex.message());
		} else
		{
			LogDebug("myAsioTestClient connect...");
			socketEx->async_write_some(boost::asio::null_buffers() ,boost::bind(&myAsioTestClient::handleWrite ,this ,socketEx ,boost::asio::placeholders::error));
		}
	}

	void handleWrite(socket_ptr socketEx ,boost::system::error_code err)
	{
		if ( err )
		{
			LogErr("myAsioTestClient handleWritet,ex=" << err.message());
			return;
		} else
		{
			LogDebug("myAsioTestClient handleWritet.....");
			boost::system::error_code write_err;
			std::string str = "hello,boost asio!are you ok?";
			int wlen = socketEx->write_some(boost::asio::buffer(str.c_str() ,str.length()) ,write_err);
			if ( write_err )
			{
				LogErr("myAsioTestClient handleWritet write some,ex=" << write_err.message());
				return;
			} else
			{
				LogDebug("myAsioTestClient handleWritet write some,complete size=" << wlen);
			}
			CThread::sleep_for(5000);
			socketEx->async_write_some(boost::asio::null_buffers() ,boost::bind(&myAsioTestClient::handleWrite ,this ,socketEx ,boost::asio::placeholders::error));
		}

	}

private:
	io_service_ptr io_service;
	work_ptr work;
	acceptor_ptr acceptor;
	std::vector<thread_ptr> threads;
};


void testAsioSrvByResolver()
{
	boost::shared_ptr<myAsioTest> test(new myAsioTest());
	test->start_accept();
	test->run();

	onlyQforExitFunc();
}

void testAsioClientByResolver()
{
	boost::shared_ptr<myAsioTestClient> test(new myAsioTestClient());
	test->start_connect();
	test->run();

	onlyQforExitFunc();
}
void testAsioClientByResolverRemote()
{
	boost::shared_ptr<myAsioTestClient> test(new myAsioTestClient());
	test->start_connect_remote();
	test->run();

	onlyQforExitFunc();
}

void testAsioEx(Json::Value& js)
{
	int type = js[1].asInt();
	switch ( type )
	{
		case 0:
		testAsioSrvByResolver();
		break;
		case 1:
		testAsioClient2(); // can work
		case 2:
		testAsioClientByResolver();
		break;
		case 3:
		testAsioClientByResolverRemote();
		break;
	}
	
}



#endif