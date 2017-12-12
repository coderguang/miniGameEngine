
#ifndef _ENGINE_THREAD_TASK_H_
#define _ENGINE_THREAD_TASK_H_

#include "thread.h"
#include <atomic>
#include <condition_variable>
#include "../baseServer/baseServerDef.h"

namespace csg
{
	// �����߳�,���� threadManager ����
	class CTask
	{
		friend class CThreadManager;
	protected:

		virtual void active(int threadCount = 1);
		
		//�����߳�
		virtual int setExit();

		//ֹͣ�߳�
		virtual int setStop();

		//��ֹͣ�лָ�
		virtual int runFromStop();

		virtual EBaseServerDef getTaskType()const;
	protected:

		CTask() :_exit(false) ,_stop(false) ,_isStart(false)
		{
		};

		virtual bool isExit()const;

		virtual bool isStop()const;

		virtual bool isStart()const;

		CLock& getLock();

		virtual void setTaskType(EBaseServerDef type);

	protected:
		std::condition_variable _cv; //��������

	private:
		//�߳�ִ�к���
		static int svc_run(void* task);

		//ʵ���߼�ִ�к���
		virtual int run();
	private:
		CTask(const CTask&)=delete;

		CTask& operator =( const CTask& ) = delete;

	private:
		std::atomic<bool> _exit; //�˳���־λ
		std::atomic<bool> _stop; //��ͣ��־λ

		std::atomic<bool> _isStart; //������־
		std::atomic<int> _threadCount; //�߳���

		CLock _lock;
		
		EBaseServerDef _serverType;
	};
}
#endif