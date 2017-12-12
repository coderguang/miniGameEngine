
#include "engine/net/session/session.h"
#include "framework/log/Log.h"
#include "framework/util/typetransform.h"

csg::CSession::CSession(int socketfd ,std::string& addr ,int port ,bool isInner) :_socketfd(socketfd) ,_remoteAddr(addr) ,_remotePort(port) ,_isClient(isInner)
{

}

int csg::CSession::getSocketfd() const
{
	return _socketfd;
}

void csg::CSession::print(std::string info)
{
	CSG_LOG_DEBUG("CCSession::print:" << info << ",remoteaddr="<<_remoteAddr<<",port="<<ToStr(_remotePort));
}

csg::CSession::~CSession()
{

}

