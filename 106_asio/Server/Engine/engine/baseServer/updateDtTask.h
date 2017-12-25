
#ifndef _ENGINE_BASE_SERVER_UPDATE_DT_TASK_H_
#define _ENGINE_BASE_SERVER_UPDATE_DT_TASK_H_

#include "baseServerDef.h"

namespace csg
{
	class CUpdateDtTask
	{
	public:
		CUpdateDtTask()
		{
			
		}
		virtual ~CUpdateDtTask()
		{
		};
	protected:
		virtual int run();
	};


}
#endif
