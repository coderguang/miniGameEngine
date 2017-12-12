#ifndef _FRAMEWORK_UTIL_COUNTER_HANDLER_H_
#define _FRAMEWORK_UTIL_COUNTER_HANDLER_H_

#include "framework/io/IOHandler.h"
#include <atomic>
#include <string>

namespace csg
{

	class CCounterHandler
	{
	public:
		CCounterHandler(const std::string& name);
		virtual ~CCounterHandler();
		virtual void print(IIOHandler* handle);

		void increaseCount(int add);

		void decreaseCount(int dec);

		void increaseCountEx(int add);

		void decreaseCountEx(int dec);

	private:
		CCounterHandler()
		{
			_count = 0;
			_countEx = 0;
		}
		CCounterHandler(const CCounterHandler&)
		{
		}
		std::string _name;
		std::atomic_long _count;
		std::atomic_long _countEx;
	};
}
#endif