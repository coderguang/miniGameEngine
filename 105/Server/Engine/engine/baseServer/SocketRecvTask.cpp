#include "engine/def/environment_def.h"
#include "engine/baseServer/SocketRecvTask.h"
#include "../net/socket/WinSocket.h"
#include "framework/log/Log.h"
#include "framework/util/typetransform.h"
#include "framework/util/sysUtil.h"
#include "../net/socket/socketManager.h"
#include "engine/net/socket/LinuxSocket.h"

using namespace csg;

static const int DEFAULT_BACK_UP_NUM = 10;
static const int DEFAULT_MAX_CONNECT_NUM = 10000;

csg::CSocketRecvTask::~CSocketRecvTask()
{
#ifdef CSG_WIN
	CWinSocket::close(_socketfd);
	CWinSocket::clearWinSocket();
#elif defined(CSG_LINUX)
	CLinuxSocket::closeSocket(_socketfd);
#endif 


}

int csg::CSocketRecvTask::init(int family ,int type ,int protocol ,int port ,std::string host ,bool isInnner)
{
	_family = family;
	_type = type;
	_protocol = protocol;
	_port = port;
	_innerPort = isInnner;
	_host = host;
	return CSG_RETURN_OK;
}

int csg::CSocketRecvTask::startListen()
{
	_isClient = false;
	int result = -1;
#ifdef CSG_WIN
	 result=initWinSocket();
#elif defined(CSG_LINUX)
	 result=initLinuxSocket();
#endif // CSG_WIN
	 if ( -1 == result )
	 {
		 return CSG_RETURN_ERROR;
	 }

	csg_thread recvThread(CSocketRecvTask::svc_run ,this);
	recvThread.detach();

	return CSG_RETURN_OK;
}

int csg::CSocketRecvTask::startConnect()
{
	_isClient = true;
	_socketfd = CSocketHelper::getClientSocket(_family ,_type ,_protocol ,_port ,_host);
	if ( -1 == _socketfd )
	{
		LogDebug("tcsg::CSocketRecvTask::startConnect failed");
		return -1;
	}
	csg_thread recvThread(CSocketRecvTask::svc_run ,this);
	recvThread.detach();
	return _socketfd;
}

int csg::CSocketRecvTask::svc_run(void* task)
{
	CSocketRecvTask *t = (CSocketRecvTask*) task;
	if ( !t )
	{
		assert(false);
		return CSG_RETURN_ERROR;
	}
	t->run();
	return CSG_RETURN_OK;
}

int csg::CSocketRecvTask::run()
{

	if ( _isClient )
	{
		doRecvLoop();
	} else
	{
		LogSys("CSocketRecvTask::run listen start,port=" << ToStr(_port));
#ifdef CSG_WIN
		doWinLoop();
#elif defined(CSG_LINUX)
		doLinuxLoop();
#endif
		LogSys("CSocketRecvTask::run exit");
	}
	return 0;
}





void csg::CSocketRecvTask::doRecvLoop()
{
	LogSys("CSocketRecvTask::doRecvLoop,ip=" <<_host<<",port="<<ToStr(_port));
	std::unique_lock<CLock> lock(getLock());
	const int SOCKET_CLIENT_BUFFER_MAX_SIZE = 1024 * 2;
	char buffer[SOCKET_CLIENT_BUFFER_MAX_SIZE];
	while ( !isExit() )
	{
		if ( isStop() )
		{
			LogSys("CSocketRecvTask::doRecvLoop waiting");
			_cv.wait(lock);
		}
		memset(buffer ,0,SOCKET_CLIENT_BUFFER_MAX_SIZE);
		int readRecvSize = 0;
#ifdef CSG_WIN
		readRecvSize = recv(_socketfd ,buffer ,SOCKET_CLIENT_BUFFER_MAX_SIZE ,0);
#elif defined(CSG_LINUX)
		readRecvSize=CLinuxSocket::Recv(_socketfd,buffer,SOCKET_CLIENT_BUFFER_MAX_SIZE,0);
#endif
		if ( readRecvSize > 0 )
		{
			//CSG_LOG_SYS("CSocketRecvTask::doRecvLoop,readSize=" <<readRecvSize);
			CSocketHelper::onRecvMsg(_socketfd ,buffer,readRecvSize);

		}
		CThread::sleep_for(100);
	}
	LogSys("CSocketRecvTask::run exit ip = " <<_host<<" ,port = "<<ToStr(_port));
}

#ifdef CSG_WIN
DWORD WINAPI csg::CSocketRecvTask::workerThreadRun(LPVOID IpParam)
{
	HANDLE CompletionPort = (HANDLE) IpParam;

	while ( true )
	{
		DWORD BytesTransferred;
		LPOVERLAPPED IpOverlapped;
		CSG_SOCKET_DATA* PerHandleData = NULL;
		CSG_SOCKET_IO_DATA* PerIoData = NULL;
		DWORD Flags = 0;
		BOOL bRet = false;
		bRet = CWinSocket::getQueuedCompletionStatus(CompletionPort ,&BytesTransferred ,(PULONG_PTR) &PerHandleData ,(LPOVERLAPPED*) &IpOverlapped ,INFINITE);//�˴����Խ�IpOverlapped��ΪPerIoData��Ȼ������CONTAINING_RECORDע�͵�
		if ( bRet == 0 )
		{
			int errorCode = CSysUtil::getLastError();
			CSG_RECORD_ERROR(" GetQueuedCompletionStatus");
			CSocketHelper::onDisconnected(PerHandleData->socketfd ,errorCode);
			continue;
		}
		PerIoData = (CSG_SOCKET_IO_DATA*) CONTAINING_RECORD(IpOverlapped ,CSG_SOCKET_IO_DATA ,overlapped);
		//�����������ǣ�����һ���ṹ��ʵ���еĳ�Ա�ĵ�ַ��ȡ�������ṹ��ʵ���ĵ�ַ
		//PER_IO_DATA�ĳ�Աoverlapped�ĵ�ַΪ&IpOverlapped������Ϳ��Ի��PER_IO_DATA�ĵ�ַ

		// ������׽������Ƿ��д�����
		if ( 0 == BytesTransferred )
		{
			CWinSocket::close(PerHandleData->socketfd);
			free(PerHandleData);
			free(PerIoData);
			continue;
		}
 		
		CSocketHelper::onRecvMsg(PerHandleData->socketfd ,PerIoData->buffer ,BytesTransferred);

		// Ϊ��һ���ص����ý�����I/O��������
		ZeroMemory(&( PerIoData->overlapped ) ,sizeof(OVERLAPPED)); // ����ڴ�
		PerIoData->databuff.len = DATA_BUFF_SOCKET_SIZE;
		PerIoData->databuff.buf = PerIoData->buffer;//buf�Ǹ�ָ�룬��һ���̻����buffer������
		PerIoData->operationType = 0;   // read
		DWORD RecvBytes;
		CWinSocket::recv(PerHandleData->socketfd ,&( PerIoData->databuff ) ,1 ,&RecvBytes ,&Flags ,&( PerIoData->overlapped ) ,NULL);
	}
}

int csg::CSocketRecvTask::initWinSocket()
{
	CWinSocket::InitSocket();
	_completionPort = CSocketManager::instance()->getIOCPPort();
	_socketfd = CWinSocket::getSocket(_family ,_type ,_protocol);

	if ( -1 == _socketfd )
	{
		CSG_RECORD_ERROR("CSocketRecvTask::init listen failed");
		return CSG_RETURN_ERROR;
	}

	int bindResult = CWinSocket::bind(_socketfd ,_family ,_port ,INADDR_ANY);

	if ( -1 == bindResult )
	{
		CSG_RECORD_ERROR("CSocketRecvTask::init bind failed");
		return CSG_RETURN_ERROR;
	}

	int listenResult = CWinSocket::listen(_socketfd ,DEFAULT_BACK_UP_NUM);
	if ( -1 == listenResult )
	{
		CSG_RECORD_ERROR("CSocketRecvTask::init listen failed");
		return CSG_RETURN_ERROR;
	}
	return CSG_RETURN_OK;
}

void csg::CSocketRecvTask::doWinLoop()
{
	std::unique_lock<CLock> lock(getLock());
	while ( !isExit() )
	{
		if ( isStop() )
		{
			LogSys("CSocketRecvTask::run waiting");
			_cv.wait(lock);
		}
		sockaddr saRemote;
		int RemoteLen = sizeof( saRemote );
		int acceptSocket = CWinSocket::accept(_socketfd ,(sockaddr*) &saRemote ,&RemoteLen);
		if ( SOCKET_ERROR == acceptSocket )
		{
			CSG_RECORD_ERROR("CSocketRecvTask::run accept failed!");
			assert(false);
			continue;
		}
		// �����������׽��ֹ����ĵ����������Ϣ�ṹ
		CSG_SOCKET_DATA * PerHandleData = new CSG_SOCKET_DATA;
		PerHandleData->socketfd = acceptSocket;
		memcpy(&PerHandleData->clientAddr ,&saRemote ,RemoteLen);


		// �������׽��ֺ���ɶ˿ڹ���
		CWinSocket::createIOCPPort((HANDLE) ( PerHandleData->socketfd ) ,_completionPort ,(DWORD) PerHandleData ,0);


		// ��ʼ�ڽ����׽����ϴ���I/Oʹ���ص�I/O����
		// ���½����׽�����Ͷ��һ�������첽
		// WSARecv��WSASend������ЩI/O������ɺ󣬹������̻߳�ΪI/O�����ṩ����    
		// ��I/O��������(I/O�ص�)
		CSG_SOCKET_IO_DATA* PerIoData = new CSG_SOCKET_IO_DATA;
		ZeroMemory(&( PerIoData->overlapped ) ,sizeof( OVERLAPPED ));
		PerIoData->databuff.len = DATA_BUFF_SOCKET_SIZE;
		PerIoData->databuff.buf = PerIoData->buffer;
		PerIoData->operationType = 0;   // read;

		DWORD RecvBytes;
		DWORD Flags = 0;  //WSARecv�е�1����������lpBuffersֻ����һ��WSABUF��Flags���������ͨ����
		CWinSocket::recv(PerHandleData->socketfd ,&( PerIoData->databuff ) ,1 ,&RecvBytes ,&Flags ,&( PerIoData->overlapped ) ,NULL);//PerIoData->overlapped����CONTAINING_RECORD�ĵ�һ������

		std::string remoteAddr(inet_ntoa(PerHandleData->clientAddr.sin_addr));
		int remotePort = ntohs(PerHandleData->clientAddr.sin_port);

		CSocketHelper::onConnected(PerHandleData->socketfd ,remoteAddr ,remotePort ,_innerPort);
	}
}


#elif defined(CSG_LINUX)

int csg::CSocketRecvTask::initLinuxSocket()
{
	_socketfd = CLinuxSocket::getSocket(_family ,_type ,_protocol);

	if ( -1 == _socketfd )
	{
		CSG_RECORD_ERROR("CSocketRecvTask::init listen failed");
		return CSG_RETURN_ERROR;
	}

	struct sockaddr_in serveraddr;
	serveraddr.sin_family = _family;
	serveraddr.sin_addr.s_addr = INADDR_ANY;
	serveraddr.sin_port = htons(_port);
	memset(&( serveraddr.sin_zero ) ,'\0' ,8);

	int bindResult = CLinuxSocket::Bind(_socketfd ,( struct sockaddr * )&serveraddr ,sizeof(serveraddr));

	if ( -1 == bindResult )
	{
		CSG_RECORD_ERROR("CSocketRecvTask::init bind failed");
		return CSG_RETURN_ERROR;
	}

	int listenResult = CLinuxSocket::Listen(_socketfd ,DEFAULT_BACK_UP_NUM);
	if ( -1 == listenResult )
	{
		CSG_RECORD_ERROR("CSocketRecvTask::init listen failed");
		return CSG_RETURN_ERROR;
	}

	_epollfd = -1;

	_events = (epoll_event*) calloc(DEFAULT_MAX_CONNECT_NUM ,sizeof(struct epoll_event));

	if ( ( _epollfd = CLinuxSocket::Epoll_create(DEFAULT_MAX_CONNECT_NUM) ) == -1 )
	{
		CSG_RECORD_ERROR("CSocketRecvTask::init epoll create failed");
		return CSG_RETURN_ERROR;
	}

	int fdmax=_socketfd;

	_ev.events = EPOLLIN;
	_ev.data.fd = fdmax;

	if ( CLinuxSocket::Epoll_ctl(_epollfd ,EPOLL_CTL_ADD ,fdmax ,&_ev)<0 )
	{
		CSG_RECORD_ERROR("CSocketRecvTask::init epoll_ctl create failed");
		return CSG_RETURN_ERROR;
	}
	return CSG_RETURN_OK;
}

void csg::CSocketRecvTask::doLinuxLoop(){

	std::unique_lock<CLock> lock(getLock());
	while ( !isExit() )
	{
		if ( isStop() )
		{
			LogSys("CSocketRecvTask::run waiting");
			_cv.wait(lock);
		}

		int res = CLinuxSocket::Epoll_wait(_epollfd ,_events ,DEFAULT_MAX_CONNECT_NUM ,-1);
		for (int index = 0; index < res; index++ )
		{
			int client_fd = _events[index].data.fd;//get the first events

			if ( client_fd == _socketfd )
			{//new connections
				struct sockaddr_in clientaddr;
				socklen_t addrlen = sizeof( clientaddr );
				int newfd = CLinuxSocket::Accept(_socketfd ,( struct sockaddr * )&clientaddr ,&addrlen);
				if ( -1 != newfd )
				{
					_ev.events = EPOLLIN;
					_ev.data.fd = newfd;
					if ( CLinuxSocket::Epoll_ctl(_epollfd ,EPOLL_CTL_ADD ,newfd ,&_ev) < 0 )
					{
						LogDebug("CSocketBase::Epoll_ctl faild when add new sockfd");
						continue;
					} else
					{
						LogDebug("CSocketBase::add new sockfd socketfd="<<ToStr(newfd));
						std::string remoteAddr(inet_ntoa(clientaddr.sin_addr));
						int remotePort = ntohs(clientaddr.sin_port);
						CSocketHelper::onConnected(newfd ,remoteAddr ,remotePort ,_innerPort);
					}
				}
				continue;
			} else
			{
				if ( _events[index].events&EPOLLHUP )
				{
					int result=CLinuxSocket::Epoll_ctl(_epollfd ,EPOLL_CTL_DEL ,client_fd ,&_ev);
					int lastError=CSysUtil::getLastError();
					if ( result< 0 )
					{
						LogDebug("CSocketBase::del the socket="<<ToStr(client_fd));
					} else
					{
						LogDebug("CSocketBase::the socket="<<ToStr(client_fd)<<" disconneted....");
					}
					CLinuxSocket::closeSocket(client_fd);

					CSocketHelper::onDisconnected(client_fd,lastError);

					continue;
				}
				if ( _events[index].events&EPOLLIN )
				{
					char buf[DATA_BUFF_SOCKET_SIZE];
					memset(buf ,'\0' ,sizeof( buf ));
					int nbytes=0;
					if ( ( nbytes = CLinuxSocket::Recv(client_fd ,buf ,sizeof( buf ) ,0) ) <= 0 )
					{
						if ( nbytes == 0 )
						{
							LogDebug("CSocketBase::sockett="<<ToStr(client_fd)<<" is hung up....");
						} else
						{
							LogDebug("CSocketBase::sockett="<<ToStr(client_fd)<<" recv error....");
						}
						CLinuxSocket::closeSocket(client_fd);
						int lastError=CSysUtil::getLastError();
						CSocketHelper::onDisconnected(client_fd,lastError);
					} else
					{
						//CSG_LOG_DEBUG("CSocketBase::sockett="<<ToStr(client_fd)<<"get msg="<<std::string(buf));

						CSocketHelper::onRecvMsg(client_fd ,buf,nbytes);
					}
				}
			}
		}
	}
}

#endif

