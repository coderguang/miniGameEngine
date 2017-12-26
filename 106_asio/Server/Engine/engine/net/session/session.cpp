#include "engine/net/session/session.h"

csg::CSession::CSession():_isInner(false),_status(ESessionStatusWaitConnecting),_sessionType(ESessionTypeClient)
{

}

csg::CSession::~CSession()
{
	if ( _socket )
	{
		_socket->close();
	}
}

void csg::CSession::setInner(bool isInner)
{
		_isInner = isInner;
}

bool csg::CSession::isInner() const
{
	return _isInner;
}

void csg::CSession::setSocket(boost_socket_ptr& socket)
{
	_socket = socket;
}

boost_socket_ptr& csg::CSession::getSocket()
{
	return _socket;
}

void csg::CSession::setType(int type)
{
	_sessionType = type;
}

int csg::CSession::getType() const
{
	return _sessionType;
}

void csg::CSession::setStatus(int status)
{
	_status = status;
}

int csg::CSession::getStatus()
{
	return _status;
}

void csg::CSession::setSocketId(int id)
{
	_socketId = id;
}

int csg::CSession::getSocketId() const
{
	return _socketId;
}
