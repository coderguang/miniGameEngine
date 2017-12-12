
#ifndef _FRAMEWORK_LOG_LOG_H_
#define _FRAMEWORK_LOG_LOG_H_

#include <iostream>

namespace csg
{
	class CLog
	{
	public:
		void Log(std::string msg ,std::string type)
		{
			std::cout << "type=" << type << ",msg=" << msg << std::endl;
		}

		void Print(std::string msg ,std::string type)
		{
			std::cout <<"type=" << type << ",msg=" << msg << std::endl;
		}
	};
}

#endif