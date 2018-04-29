#ifndef _ENGINE_THREAD_THREAD_H_
#define _ENGINE_THREAD_THREAD_H_

#include <thread>
#include "framework/datetime/datetime.h"

namespace csg
{
	typedef std::thread::id csg_thread_id;
	class CThread
	{
	public:

		static int threadId();

		static int pid();

		static void sleep_for(long64_t milliseconds);

		static void sleep_until(CDateTime dt);

		static void yeild();

	private:

		static csg_thread_id get_id();
	};

}
#endif