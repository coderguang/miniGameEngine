#ifndef _ENGINE_BASE_SERVER_SOCKET_SEND_TASK_H_
#define _ENGINE_BASE_SERVER_SOCKET_SEND_TASK_H_

#include "../thread/task.h"

namespace csg
{
	//���߳�ֻ�����MQ�з�������
	class CSocketSendTask :public virtual CTask
	{
	public:
		CSocketSendTask() :CTask()
		{
			setTaskType(EBaseServerSocketSend);
		}

		static int svn_run(void* task);

	protected:
		virtual int run();



	};


}
#endif