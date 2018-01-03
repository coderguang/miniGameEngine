#include "engine/net/session/session.h"
#include "engine/net/protocol/protocol.h"
#include <limits.h>
#include "../../rpc/rmiObject.h"

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

void csg::CSession::setProtocol(IProtocolPtr protocol)
{
	_protocol = protocol;
}

int csg::CSession::handleRecvData(const void* inData ,const int len)
{
	if ( NULL == _protocol )
	{
		assert(false);
		return -1;
	}
	CAutoLock l(_readLock);
	return _protocol->handleRecvData(inData ,len);
}

int csg::CSession::handleSendData(const CSessionPtr& session ,const void* data ,const int len)
{
	if ( NULL == _protocol )
	{
		assert(false);
		return -1;
	}
	CAutoLock l(_writeLock);
	return _protocol->handleSendData(this ,data ,len);
}

int csg::CSession::handlePacketRecvData()
{
	if (NULL == _protocol)
	{
		assert(false);
		return -1;
	}
	CAutoLock l(_readLock);
	return _protocol->handleReadData(this);
}

int csg::CSession::getCallBackId()
{
	if ( _callBackId < INT_MAX )
	{
		return _callBackId++;
	} else
	{
		_callBackId = 1;
		return _callBackId;
	}
}

void csg::CSession::addCallBackObject(int callBackId ,CRMIObjectBindPtr& object)
{
	MapRMIObjectBind::const_iterator it = _callBackMap.find(callBackId);
	assert(it == _callBackMap.cend());
	_callBackMap[callBackId] = object;
}

bool csg::CSession::getCallBackObject(int callBackId ,CRMIObjectBindPtr& backObject)
{
	MapRMIObjectBind::const_iterator it = _callBackMap.find(callBackId);
	if ( it != _callBackMap.cend() )
	{
		backObject = it->second;
		return true;
	}
	backObject = NULL;
	return false;
}

// char* csg::CSession::getRecvDataPoint()
// {
// 	if ( NULL == _protocol )
// 	{
// 		assert(false);
// 		return NULL;
// 	}
// 	CAutoLock l(_readLock);
// 	return _protocol->getRecvDataPoint();
// }
// 
// int csg::CSession::getRecvDataSize()
// {
// 	if ( NULL == _protocol )
// 	{
// 		assert(false);
// 		return NULL;
// 	}
// 	return _protocol->getRecvDataSize();
// }
// void csg::CSession::addRecvDataSize(int len)
// {
// 	if ( NULL == _protocol )
// 	{
// 		assert(false);
// 		return ;
// 	}
// 	_protocol->addRecvDataSize(len);
// }
