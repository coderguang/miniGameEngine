#include "engine/baseServer/SocketClient.h"
#include "../core/csgIoMgr.h"
#include "framework/util/typetransform.h"
#include "boost/asio/connect.hpp"

csg::CSocketClient::CSocketClient()
{
	_session = CSessionPtr(new CSession());
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
		disconnect(session);
	} else
	{
		LogDebug("CSocketClient::handleConnect connect...");
		startRead(session);
	}
}

void csg::CSocketClient::handleWrite(CSessionPtr session ,boost::system::error_code err)
{
	if ( err )
	{
		LogErr("CSocketClient::handleWrite,ex=" << err.message());
		disconnect(session);
		return;
	} else
	{
		LogDebug("CSocketClient::handleWrite.....");
		boost::system::error_code write_err;
		std::string str = "hello,boost asio!are you ok?";
		int wlen = session->getSocket()->write_some(boost::asio::buffer(str.c_str() ,str.length()) ,write_err);
		if ( write_err )
		{
			LogErr("CSocketClient::handleWrite write some,ex=" << write_err.message());
			disconnect(session);
			return;
		} else
		{
			LogDebug("CSocketClient::handleWrite write some,complete size=" << wlen);
		}
		
	}
}

void csg::CSocketClient::disconnect(CSessionPtr session)
{
	session->getSocket()->close();
	session->setStatus(ESessionStatusDisConnected);
}

void csg::CSocketClient::startRead(CSessionPtr session)
{
	session->getSocket()->non_blocking(true);
	session->getSocket()->async_read_some(boost::asio::null_buffers() ,
										  boost::bind(&CSocketClient::handleRead ,this ,session ,boost::asio::placeholders::error ,boost::asio::placeholders::bytes_transferred));
}

void csg::CSocketClient::handleRead(CSessionPtr session ,boost::system::error_code error ,size_t bytes_transferred)
{
	if ( error )
	{
		LogErr("CSocketClient::handleRead,msg=" << error.message());
		disconnect(session);
		return;
	}
	boost::system::error_code read_err;
	//int len = session->getSocket()->read_some(boost::asio::buffer(session->getRecvDataPoint(),session->getRecvDataSize()) ,read_err);
	//暂时先不考虑效率
	char tt[SERIALIZE_MAX_RESIZE];
	memset(&tt ,'\0' ,SERIALIZE_MAX_RESIZE);
	int len = session->getSocket()->read_some(boost::asio::buffer(tt) ,read_err);
	if ( read_err )
	{
		LogErr("CSocketClient::handleRead error read error,msg=" << read_err.message());
		disconnect(session);
		return;
	} else
	{
		//session->addRecvDataSize(len);
		//LogDebug("CSocketClient::handleRead,msg="<< ",read size=" << len);
	}
	startRead(session);
}


