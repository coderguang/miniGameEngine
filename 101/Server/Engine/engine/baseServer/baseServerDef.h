#ifndef _ENGINE_BASE_SERVER_DEF_H_
#define _ENGINE_BASE_SERVER_DEF_H_

enum EBaseServerDef
{
	EBaseServerUpdateDt = 1 ,//ʱ����·���
	EBaseServerLoggerWritter = 2 ,//log������


	EBaseServerAll = EBaseServerUpdateDt | EBaseServerLoggerWritter,  //���з�����
};


const int CSERVER_UPDATE_DATE_AMOUNT = 1;  //ʱ����·������߳�����
const int CSERVER_LOG_WRITTER_AMOUNT = 1;  //log�������߳�����

#endif