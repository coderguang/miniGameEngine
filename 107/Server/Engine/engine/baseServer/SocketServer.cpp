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
	CSessionPtr session=new CSession();
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
		CCsgProtocolPtr protocol = new CCsgProtocol(PROTOCOL_RECV_MAX_SIZE_LIMIT_CLIENT,PROTOCOL_RECV_BUFF_MAX_SIZE_LIMIT_CLIENT);
		session->setProtocol(protocol);
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
		if (-1 == session->handleRecvData(tt, len) ){
			LogDebug(__FUNCTION__<< ",read error len =" << len);
			disconnect(session);
			return;
		}
		LogDebug("CSocketServer::handleRead"<< ",read size=" << len);
	}
	startRead(session);
}

void csg::CSocketServer::disconnect(CSessionPtr session)
{
	session->getSocket()->close();
	session->setStatus(ESessionStatusDisConnected);
	CSessionMgr::instance()->delSession(session);
}

