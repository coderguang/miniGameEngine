#include "engine/baseServer/SocketServer.h"
#include "../core/csgIoMgr.h"
#include "../net/session/session.h"
#include "../net/session/sessionMgr.h"

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

void csg::CSocketServer::startAccept()
{
	boost_socket_ptr socket(new boost_socket(*CCsgIoMgr::instance()->getIoService()));
	CSessionPtr session = new CSession();
	session->setSocket(socket);
	session->setInner(_isInner);
	session->setType(_sessionType);
	session->setStatus(ESessionStatusWaitConnecting);
	acceptor->async_accept(*session->getSocket() ,boost::bind(&CSocketServer::handleAccept ,this ,session,boost::asio::placeholders::error));
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
		session->setStatus(ESessionStatusConnected);
		CSessionMgr::instance()->addSession(session);
		startRead(session);
		startAccept();
	} else
	{
		LogDebug("myAsioTest accept...,err=" << error.message() << ",code=" << error.value());
		startAccept();
	}
}

void csg::CSocketServer::startRead(CSessionPtr& session)
{
	session->getSocket()->non_blocking(true);
	session->getSocket()->async_read_some(boost::asio::null_buffers() ,
										  boost::bind(&CSocketServer::handleRead ,this ,session ,boost::asio::placeholders::error ,boost::asio::placeholders::bytes_transferred));
}

void csg::CSocketServer::handleRead(CSessionPtr& session ,boost::system::error_code error ,size_t bytes_transferred)
{
	if ( error )
	{
		LogErr("CSocketServer::handleRead,msg=" << error.message());
		disconnect(session);
		return;
	}
	boost::system::error_code read_err;

	const int read_len = 100;
	char buf[read_len];
	memset(buf ,'\0' ,read_len);
	int len = session->getSocket()->read_some(boost::asio::buffer(buf) ,read_err);
	if ( read_err )
	{
		LogErr("CSocketServer::handleRead error read error,msg=" << read_err.message());
		disconnect(session);
		return;
	} else
	{
		std::string bufstr(buf);
		LogDebug("CSocketServer::handleRead,msg=" << bufstr << ",read size=" << len);
	}
	startRead(session);
}

void csg::CSocketServer::disconnect(CSessionPtr& session)
{
	session->getSocket()->close();
	session->setStatus(ESessionStatusDisConnected);
	CSessionMgr::instance()->delSession(session);
}

