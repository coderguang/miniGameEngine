#ifndef _TEST_ASIO_H_
#define _TEST_ASIO_H_

#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>

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

void testAsio(Json::Value& js) {
	int type = js[1].asInt();
	if ( 0 == type)
	{
		testAsioSrv();
	} else if ( 1 == type )
	{
		testAsioClient();
	} else if ( 2 == type )
	{
		testOldClient();
	}
}

#endif