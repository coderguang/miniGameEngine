
#ifndef _ENGINE_LOCK_LOCK_H_
#define _ENGINE_LOCK_LOCK_H_

#include "engine/def/csg_def.h"

#ifdef CSG_LINUX
#include <pthread.h>
#endif

namespace csg
{
	//

	class CLock
	{
	public:
		
		CLock()
		{
#ifdef CSG_WIN32
			InitializeCriticalSection(&_lock);
#elif defined(CSG_LINUX)
			pthread_mutexattr_t attr;
			pthread_mutexattr_init(&attr);

			pthread_mutexattr_settype(&attr,PTHREAD_MUTEX_RECURSIVE_NP);
			pthread_mutex_init(&_lock,&attr);
			pthread_mutexattr_destroy(&attr);
#endif
		}
		
		virtual ~CLock()
		{
#ifdef CSG_WIN32
			DeleteCriticalSection(&_lock);
#elif defined(CSG_LINUX)
			pthread_mutex_destroy(&_lock);
#endif
		}

		void lock()
		{
#ifdef CSG_WIN32
			EnterCriticalSection(&_lock);
#elif defined(CSG_LINUX)
			pthread_mutex_lock(&_lock);
#endif
		}
		 void unlock()
		{
#ifdef CSG_WIN32
			::LeaveCriticalSection(&_lock);
#elif defined(CSG_LINUX)
			::pthread_mutex_unlock(&_lock);
#endif
		}
		
	private:
		CLock(const CLock&)
		{
		
		}

#ifdef CSG_WIN32
		CRITICAL_SECTION _lock;
#elif defined(CSG_LINUX)
		pthread_mutex_t _lock;
#endif
	};

	
	template<typename T>
	class CAutoLockT
	{
	public:
		CAutoLockT(T* lock) :_lock(lock)
		{
			_lock->lock();
		}
		CAutoLockT(T &lock) :_lock(&lock)
		{
			_lock->lock();
		}
		virtual ~CAutoLockT()
		{
			_lock->unlock();
		}	
	private:
		CAutoLockT(const CAutoLockT&)
		{
		
		}
		T* _lock;
	};

	typedef CAutoLockT<CLock> CAutoLock;

}
#endif