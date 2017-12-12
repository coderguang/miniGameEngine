#ifndef _ENGINE_BASE_SERVER_DEF_H_
#define _ENGINE_BASE_SERVER_DEF_H_

enum EBaseServerDef
{
	EBaseServerUpdateDt = 1 ,//时间更新服务
	EBaseServerLoggerWritter = 2 ,//log服务器


	EBaseServerAll = EBaseServerUpdateDt | EBaseServerLoggerWritter,  //所有服务器
};


const int CSERVER_UPDATE_DATE_AMOUNT = 1;  //时间更新服务器线程数量
const int CSERVER_LOG_WRITTER_AMOUNT = 1;  //log服务器线程数量

#endif