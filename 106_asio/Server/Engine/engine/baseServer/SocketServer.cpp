#include "engine/baseServer/SocketServer.h"
#include "../core/csgIoMgr.h"
#include "../net/session/session.h"
#include "../net/session/sessionMgr.h"
#include "../net/protocol/csgProtocol.h"

void csg::CSocketServer::init(int port ,bool isInner ,int sessionType)
{
	_port = port;
	_isInner = isInner;
	_sessionType = sessionType;
}

int csg::CSocketServer::getPort() const
{
	return _port;
}

bool csg::CSocketServer::isInner()const
{
	return _isInner;
}

void csg::CSocketServer::startListen()
{
	acceptor = boost_acceptor_ptr(new boost_acceptor(*CCsgIoMgr::instance()->getIoService() ,boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4() ,_port)));
	startAccept();
}

void csg::CSocketServer::stop()
{
	acceptor->close();
}

void csg::CSocketServer::startAccept()
{
	boost_socket_ptr socket(new boost_socket(*CCsgIoMgr::instance()->getIoService()));
	CSessionPtr session(new CSession());
	session->setSocket(socket);
	session->setInner(_isInner);
	session->setType(_sessionType);
	session->setStatus(ESessionStatusWaitConnecting);
	acceptor->async_accept(*session->getSocket() ,boost::bind(&CSocketServer::handleAccept ,shared_from_this() ,session,boost::asio::placeholders::error));
}

void csg::CSocketServer::handleAccept(CSessionPtr session ,const boost::system::error_code& error)
{
	LogDebug("CSocketServer::handleAccept accept...,port=" << _port);
	if ( !error )
	{
	    std:string ip = "";
		try
		{
			ip = session->getSocket()->remote_endpoint().address().to_string();
			LogDebug("CSocketServer::handleAccept accept... ,port = " << _port << ",ip=" << ip);
		} catch ( std::exception& ex )
		{
			LogDebug("CSocketServer::handleAccept accept... ,port = " << _port << " ,ex=" << ex.what());
		}
		CCsgProtocolPtr protocol = new CCsgProtocol();
		session->setProtocol(protocol);
		session->setStatus(ESessionStatusConnected);
		CSessionMgr::instance()->addSession(session);
		startRead(session);
		startAccept();
	} else
	{
		LogDebug("myAsioTest accept...,err=" << error.message() << ",code=" << error.value());
		if(error!= boost::asio::error::operation_aborted)
			startAccept();
		else
			LogDebug("myAsioTest accept...other error,err=" << error.message() << ",code=" << error.value());
	}
}

void csg::CSocketServer::startRead(CSessionPtr session)
{
	session->getSocket()->non_blocking(true);
	session->getSocket()->async_read_some(boost::asio::null_buffers() ,
										  boost::bind(&CSocketServer::handleRead , shared_from_this(),session ,boost::asio::placeholders::error ,boost::asio::placeholders::bytes_transferred));
}

void csg::CSocketServer::handleRead(CSessionPtr session ,boost::system::error_code error ,size_t bytes_transferred)
{
	if ( error )
	{
		LogErr("CSocketServer::handleRead,msg=" << error.message());
		disconnect(session);
		return;
	}
	//暂时先不考虑效率
	char tt[SERIALIZE_MAX_RESIZE];
	memset(&tt ,'\0' ,SERIALIZE_MAX_RESIZE);
	boost::system::error_code read_err;
	int len = session->getSocket()->read_some(boost::asio::buffer(tt) ,read_err);
	if ( read_err )
	{
		LogErr("CSocketServer::handleRead error read error,msg=" << read_err.message());
		disconnect(session);
		return;
	} else
	{
		session->handleRecvData(tt ,len);
		LogDebug("CSocketServer::handleRead"<< ",read size=" << len);
	}

	//session->getSocket()->async_write_some(boost::asio::null_buffers() ,boost::bind(&CSocketServer::handleWrite ,this ,session ,boost::asio::placeholders::error));

	startRead(session);
}

void csg::CSocketServer::disconnect(CSessionPtr session)
{
	session->getSocket()->close();
	session->setStatus(ESessionStatusDisConnected);
	CSessionMgr::instance()->delSession(session);
}

void csg::CSocketServer::handleWrite(CSessionPtr session ,boost::system::error_code err)
{
	if ( err )
	{
		LogErr("csg::CSocketServer,ex=" << err.message());
		disconnect(session);
		return;
	} else
	{
		LogDebug("csg::CSocketServer::handleWrite.....");
		boost::system::error_code write_err;
		std::string str = "hello,boost asio!are you ok? I'm server";
		int wlen = session->getSocket()->write_some(boost::asio::buffer(str.c_str() ,str.length()) ,write_err);
		if ( write_err )
		{
			LogErr("csg::CSocketServer::handleWrite write some,ex=" << write_err.message());
			disconnect(session);
			return;
		} else
		{
			LogDebug("csg::CSocketServer::handleWrite write some,complete size=" << wlen);
		}
		CThread::sleep_for(1000);
		//session->getSocket()->async_write_some(boost::asio::null_buffers() ,boost::bind(&CSocketServer::handleWrite ,this ,session ,boost::asio::placeholders::error));
	}
}

