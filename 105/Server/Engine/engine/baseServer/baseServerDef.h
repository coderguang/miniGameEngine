#ifndef _ENGINE_BASE_SERVER_DEF_H_
#define _ENGINE_BASE_SERVER_DEF_H_

enum EBaseServerDef
{
	EBaseServerUpdateDt = 1 ,//ʱ����·���
	EBaseServerLoggerWritter = 2 ,//log������
	EBaseServerSocketRecv=4,//����IO����
	EBaseServerSocketSend=8,//����IO����
	EBaseServerMainLogic=16,//�߼����߳�

	EBaseServerAll = EBaseServerUpdateDt | EBaseServerLoggerWritter | EBaseServerSocketRecv | EBaseServerSocketSend |EBaseServerMainLogic,  //���з�����
};


const int CSERVER_UPDATE_DATE_AMOUNT = 1;  //ʱ����·������߳�����
const int CSERVER_LOG_WRITTER_AMOUNT = 1;  //log�������߳�����
const int CSERVER_MAIN_LOGIC_AMOUNT = 1;//�߼��߳�����
const int CSERVER_SOCKET_SEND_AMOUNT = 1; //��Ϣ�����߳�


#endif