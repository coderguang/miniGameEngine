
#ifndef _ENGINE_BASE_SERVER_MAIN_LOGIC_H_
#define _ENGINE_BASE_SERVER_MAIN_LOGIC_H_
#include "baseServerDef.h"

namespace csg
{
	class CMainLogicTask
	{
	public:
		CMainLogicTask() 
		{
		
		}
		virtual ~CMainLogicTask()
		{
		}
		virtual int run();
	};
}
#endif