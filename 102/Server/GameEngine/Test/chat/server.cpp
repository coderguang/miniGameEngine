#include "server.h"
#include "engine/def/environment_def.h"
#include "framework/util/sysUtil.h"
#include "framework/log/Log.h"
#include "framework/util/typetransform.h"
#include "engine/net/socket/socket.h"


#ifdef CSG_WIN

using namespace csg;

csg::CChatServer::CChatServer(int af ,int type ,int protol ,int port ,HANDLE completionPort) :_af(af) ,_type(type) ,_protocol(protol) ,_port(port)
{
	_completionPort = completionPort;
	 CWinSocket::InitSocket();

	 _listenfd = CWinSocket::getSocket(_af ,_type ,_protocol);
	
	CWinSocket::bind(_listenfd ,_af ,_port ,INADDR_ANY);
	
	 CWinSocket::listen(_listenfd ,10);
	
	 CSG_LOG_DEBUG("����������׼�����������ڵȴ��ͻ��˵Ľ���...");
}

csg::CChatServer::~CChatServer()
{
	CWinSocket::close(_listenfd);
	CWinSocket::clearWinSocket();
}

void csg::CChatServer::startRun()
{
	std::thread th(CChatServer::run ,this);
	th.detach();
}

void csg::CChatServer::run(CChatServer* srv)
{
	srv->doRun();
}

void csg::CChatServer::doRun()
{
	while ( true )
	{
		SOCKADDR_IN saRemote;
		int RemoteLen;
		int acceptSocket;

		// �������ӣ���������ɶˣ����������AcceptEx()
		RemoteLen = sizeof(saRemote);
		acceptSocket = CWinSocket::accept(_listenfd ,(SOCKADDR*) &saRemote ,&RemoteLen);
		if ( SOCKET_ERROR == acceptSocket )
		{ // ���տͻ���ʧ��
			cerr << "Accept Socket Error: " << GetLastError() << endl;
		}
		CSG_SOCKET_DATA * PerHandleData = NULL;
		// �����������׽��ֹ����ĵ����������Ϣ�ṹ
		PerHandleData = new CSG_SOCKET_DATA;
		PerHandleData->socketfd = acceptSocket;
		memcpy(&PerHandleData->clientAddr ,&saRemote ,RemoteLen);

		// �������׽��ֺ���ɶ˿ڹ���
		CWinSocket::createIOCPPort((HANDLE) ( PerHandleData->socketfd ) ,_completionPort ,(DWORD) PerHandleData ,0);


		// ��ʼ�ڽ����׽����ϴ���I/Oʹ���ص�I/O����
		// ���½����׽�����Ͷ��һ�������첽
		// WSARecv��WSASend������ЩI/O������ɺ󣬹������̻߳�ΪI/O�����ṩ����    
		// ��I/O��������(I/O�ص�)
		CSG_SOCKET_IO_DATA* PerIoData = NULL;
		PerIoData = new CSG_SOCKET_IO_DATA;
		ZeroMemory(&( PerIoData->overlapped ) ,sizeof(OVERLAPPED));
		PerIoData->databuff.len = 1024;
		PerIoData->databuff.buf = PerIoData->buffer;
		PerIoData->operationType = 0;   // read;

		DWORD RecvBytes;
		DWORD Flags = 0;  //WSARecv�е�1����������lpBuffersֻ����һ��WSABUF��Flags���������ͨ����
		CWinSocket::recv(PerHandleData->socketfd ,&( PerIoData->databuff ) ,1 ,&RecvBytes ,&Flags ,&( PerIoData->overlapped ) ,NULL);//PerIoData->overlapped����CONTAINING_RECORD�ĵ�һ������
	}
}

#endif