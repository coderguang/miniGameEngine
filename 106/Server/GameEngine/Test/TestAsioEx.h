
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

class myAsioTest
{
public:
	myAsioTest() :w(io_service) ,socket(new boost::asio::ip::tcp::socket(io_service)),acceptor(get_io_service() ,boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4() ,8989))
	{
	};

	boost::asio::io_service& get_io_service()
	{
		return io_service;
	}
	socket_ptr& get_socket()
	{
		return socket;
	}

	void start_connect()
	{
		using namespace boost::asio;

		ip::tcp::resolver resolver(get_io_service());
		ip::tcp::resolver::query query(localhostip ,localhostport);
		
		ip::tcp::resolver::iterator iter = resolver.resolve(query);

		socket_ptr socketEx(new boost::asio::ip::tcp::socket(io_service));
		boost::asio::async_connect(*socketEx ,iter ,boost::bind(&myAsioTest::handleConnect ,this,socketEx,boost::asio::placeholders::error));

	}

	void start_accept()
	{
		socket_ptr socketEx(new boost::asio::ip::tcp::socket(io_service));
		acceptor.async_accept(*socketEx ,boost::bind(&myAsioTest::handle_accept ,this,socketEx,boost::asio::placeholders::error));
	}
	void run()
	{
		thread_ptr t(new boost::thread(boost::bind(&boost::asio::io_service::run ,&io_service)));
		threads.push_back(t);
	}

	void start_read(socket_ptr socket)
	{
		socket->async_read_some(boost::asio::null_buffers() ,boost::bind(
			&myAsioTest::handle_read ,this,socket ,boost::asio::placeholders::error ,boost::asio::placeholders::bytes_transferred));
	}

private:

	void handle_read(socket_ptr socket,boost::system::error_code error ,size_t bytes_transferred)
	{
		if ( error )
		{
			LogErr("handle_read error,msg=" << error.message());
		}
		boost::system::error_code read_err;

		std::vector<char>* buf = new std::vector<char>(1000, 0);

		//socket->async_read_some(boost::asio::buffer(*buf));
		if (read_err) {
			LogErr("handle_read error read error,msg=" << read_err.message());
		}
		
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
		}
	}

	boost::asio::io_service io_service;
	boost::asio::io_service::work w;
	socket_ptr socket;
	std::vector<thread_ptr> threads;
	boost::asio::ip::tcp::acceptor acceptor;
};

void testAsioSrvByResolver()
{
	boost::shared_ptr<myAsioTest> test(new myAsioTest());
	test->start_accept();
	//test->start_connect();
	test->run();

	onlyQforExitFunc();
}

void testAsioClientByResolver()
{
	boost::shared_ptr<myAsioTest> test(new myAsioTest());
	test->start_connect();
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
	}
	
}


#endif