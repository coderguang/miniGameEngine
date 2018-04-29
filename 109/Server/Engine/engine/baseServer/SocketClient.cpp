#include "engine/baseServer/SocketClient.h"
#include "../core/csgIoMgr.h"
#include "framework/util/typetransform.h"
#include "boost/asio/connect.hpp"
#include "../net/protocol/csgProtocol.h"
#include "../net/session/sessionMgr.h"
#include "../net/protocol/protocol.h"
#include "../net/socket/socketHelper.h"

csg::CSocketClient::CSocketClient()
{
	_session =new CSession();
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
	boost::asio::async_connect(*_session->getSocket(),iter ,boost::bind(&CSocketClient::handleConnect ,shared_from_this() ,_session,boost::asio::placeholders::error));
}

void csg::CSocketClient::pushMessage(const CMsgBlockPtr& mb)
{
	_session->pushMessage(mb);
}

csg::CSessionPtr csg::CSocketClient::getSession()
{
	return _session;
}

void csg::CSocketClient::handleConnect(CSessionPtr session ,boost::system::error_code ex)
{
	if ( ex )
	{
		LogErr("CSocketClient::handleConnect connect,ex=" << ex.message());
		CSocketHelper::disconnect(session, ESessionDisconnectConnectError);
	} else
	{
		LogDebug("CSocketClient::handleConnect connect...");
		IProtocolPtr protocol = new CCsgProtocol(PROTOCOL_RECV_MAX_SIZE_LIMIT_CLIENT,PROTOCOL_RECV_BUFF_MAX_SIZE_LIMIT_CLIENT);
		session->setProtocol(protocol);
		session->setStatus(ESessionStatusConnected);
		CSessionMgr::instance()->addSession(_session);
		CSocketHelper::startRead(session);
	}
}
