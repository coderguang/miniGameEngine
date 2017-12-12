#include "engine/net/socket/socket.h"
#include "WinSocket.h"
#include "../session/session.h"
#include "../session/sessionManager.h"
#include <string.h>
#include "framework/util/typetransform.h"
#include "../../serialize/serializestream.h"
#include "../GameEngine/Message/GameMsg.h"

int csg::CSocketHelper::getClientSocket(int family ,int type ,int protocol ,int port ,std::string ip)
{
#ifdef CSG_WIN
	CWinSocket::InitSocket();

	int socketfd = CWinSocket::getSocket(family ,type ,protocol);
	if ( INVALID_SOCKET == socketfd )
	{
		CSG_LOG_DEBUG("CSocketHelper::getClientSocket,invalid socket");
		return CSG_RETURN_ERROR;
	}
	struct sockaddr_in servaddr;
	servaddr.sin_family = family;
	servaddr.sin_port = htons(port);
	servaddr.sin_addr.S_un.S_addr = inet_addr(ip.c_str());

	if ( SOCKET_ERROR == connect(socketfd ,( struct sockaddr * )&servaddr ,sizeof(servaddr)) )
	{
		CSG_LOG_DEBUG("CSocketHelper::connect failed");
		return CSG_RETURN_ERROR;
	}
	return socketfd;
#elif defined(CSG_LINUX)

	int socketfd = CLinuxSocket::getSocket(family ,type ,protocol);
	if ( -1 == socketfd )
	{
		CSG_LOG_DEBUG("CSocketHelper::getClientSocket,invalid socket");
		return CSG_RETURN_ERROR;
	}
	struct sockaddr_in remote_addr;
	remote_addr.sin_family = family;
	remote_addr.sin_addr.s_addr = inet_addr(ip.c_str());
	remote_addr.sin_port = htons(port);

	int result=CLinuxSocket::Connect(socketfd ,( struct sockaddr* )&remote_addr ,sizeof(remote_addr));
	if ( -1 == result )
	{
		CSG_LOG_DEBUG("CSocketHelper::connect failed");
		return CSG_RETURN_ERROR;
	}
	return socketfd;
#endif
}

int csg::CSocketHelper::sendMsg(int socketfd ,const char* buf ,int len)
{
#ifdef CSG_WIN
	return CWinSocket::send(socketfd ,buf ,len ,0);
#elif defined(CSG_LINUX)

	return CLinuxSocket::Writen(socketfd ,buf ,len);
#endif
}

void csg::CSocketHelper::onConnected(int clientfd ,std::string& remoteAddr ,int remotePort ,bool isInner)
{
	CSessionPtr session = new CSession(clientfd ,remoteAddr ,remotePort ,isInner);
	session->print("onConnected");
	CSessionManager::instance()->addSession(session);
}

void csg::CSocketHelper::onDisconnected(int clientfd ,int errorCode)
{
	CSessionPtr session = CSessionManager::instance()->getSession(clientfd);
	if ( session )
	{
		session->print("onDisconnected");
	}
	CSessionManager::instance()->removeSession(clientfd);
}

void csg::CSocketHelper::onRecvMsg(int clientfd ,const char* buf ,int len)
{
	if ( len <= 0 )
	{
		return;
	}
	char tmpBuf[DATA_BUFF_SOCKET_SIZE];
	memcpy(tmpBuf ,buf ,len);
	tmpBuf[len] = '\0';
	std::string str(tmpBuf);

	CSerializeStream tmpOS;
	tmpOS.append(buf ,len);
	tmpOS.prepareToRead();
	tmpOS.setUseBitMark(true);

	Message::SeriaTestAllTest msg;
	msg.read(tmpOS);

	msg.print();

	CSG_LOG_DEBUG("CSocketHelper::onRecvMsg:size=" << ToStr(len) << ",msg=" << str);
}
