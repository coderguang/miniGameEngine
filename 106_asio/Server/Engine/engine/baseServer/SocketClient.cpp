#include "engine/baseServer/SocketClient.h"
#include "../core/csgIoMgr.h"
#include "framework/util/typetransform.h"
#include "boost/asio/connect.hpp"

csg::CSocketClient::CSocketClient()
{
	_session = new CSession();
}

void csg::CSocketClient::init(std::string ip ,int port,bool isInner)
{
	_ip = ip;
	_port = port;
	_isInner = isInner;
}

void csg::CSocketClient::startConnect()
{
	boost::asio::ip::tcp::resolver resolver(*CCsgIoMgr::instance()->getIoService());
	boost::asio::ip::tcp::resolver::query query(_ip ,ToStr(_port));
	boost::asio::ip::tcp::resolver::iterator iter = resolver.resolve(query);

	boost_socket_ptr socket(new boost::asio::ip::tcp::socket(*CCsgIoMgr::instance()->getIoService()));
	_session->setSocket(socket);
	_session->setInner(_isInner);
	_session->setStatus(ESessionStatusWaitConnecting);
	

	boost::asio::async_connect(*_session->getSocket(),iter ,boost::bind(&CSocketClient::handleConnect ,this ,_session,boost::asio::placeholders::error));
}

void csg::CSocketClient::handleConnect(CSessionPtr session ,boost::system::error_code ex)
{
	if ( ex )
	{
		LogErr("CSocketClient::handleConnect connect,ex=" << ex.message());
		session->getSocket()->close();
		session->setStatus(ESessionStatusDisConnected);
	} else
	{
		LogDebug("CSocketClient::handleConnect connect...");
		//socketEx->async_write_some(boost::asio::null_buffers() ,boost::bind(&myAsioTestClient::handleWrite ,this ,socketEx ,boost::asio::placeholders::error));
	}
}

