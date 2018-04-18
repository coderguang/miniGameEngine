#include "engine/baseServer/SocketServer.h"
#include "engine/core/csgIoMgr.h"
#include "engine/net/session/session.h"
#include "engine/net/session/sessionMgr.h"
#include "engine/net/protocol/csgProtocol.h"
#include "engine/net/protocol/csgWebSocketProtocol.h"
#include "engine/net/socket/socketHelper.h"
#include "boost/asio/basic_socket_acceptor.hpp"
#include "engine/core/csgServer.h"

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

int csg::CSocketServer::startListen()
{
	{ //must use {} to destroy accept to free port
		boost::system::error_code ec;
		boost::asio::ip::tcp::acceptor check_accept(*CCsgIoMgr::instance()->getIoService());
		check_accept.open(boost::asio::ip::tcp::v4(), ec) || check_accept.bind({ boost::asio::ip::tcp::v4(),_port }, ec);

		if (ec) {
			LogErr(__FUNCTION__ << " listen failed:" << _port << " ,msg=" << ec.message());
			CThread::sleep_for(1000);
			CCsgServer::instance()->stop();
			return -1;
		}
	}
	acceptor = boost_acceptor_ptr(new boost_acceptor(*CCsgIoMgr::instance()->getIoService() ,boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4() ,_port)));
	startAccept();
	return 0;
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
		std:string remote_ip = "";
		int remote_port = 0;
		try
		{
			remote_ip = session->getSocket()->remote_endpoint().address().to_string();
			remote_port = session->getSocket()->remote_endpoint().port();
			LogDebug("CSocketServer::handleAccept accept... ,port = " << _port << ",ip=" << remote_ip<<",client port="<<remote_port);
		} catch ( std::exception& ex )
		{
			LogDebug("CSocketServer::handleAccept accept... ,port = " << _port << " ,ex=" << ex.what());
		}
		if (isInner()) { //内部使用普通 c++ socket
			CCsgProtocolPtr protocol = new CCsgProtocol(PROTOCOL_RECV_MAX_SIZE_LIMIT_CLIENT, PROTOCOL_RECV_BUFF_MAX_SIZE_LIMIT_CLIENT);
			session->setProtocol(protocol);
		}
		else { //和客户端连接,使用websocket
			CCsgWebSocketProtocolPtr protocol = new CCsgWebSocketProtocol(PROTOCOL_RECV_MAX_SIZE_LIMIT_CLIENT, PROTOCOL_RECV_BUFF_MAX_SIZE_LIMIT_CLIENT);
			session->setProtocol(protocol);
		}
		session->setAddress(remote_ip, remote_port);
		session->setStatus(ESessionStatusConnected);
		CSessionMgr::instance()->addSession(session);
		CSocketHelper::startRead(session);
		startAccept();
	} else
	{
		LogDebug("myAsioTest accept...,err=" << error.message() << ",code=" << error.value());
		startAccept();
	}
}
