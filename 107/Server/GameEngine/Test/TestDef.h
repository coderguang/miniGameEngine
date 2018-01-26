#ifndef _TEST_DEF_
#define _TEST_DEF_

#include <string>
#include <iostream>
#include "framework/log/Log.h"

namespace csg
{
	static const std::string test_royalchen_url = "test.royalchen.com";
	static const std::string test_royalchen_ip = "123.207.87.135";

	static const std::string royalchen_url = "login.royalchen.com";
	static const std::string royalchen_ip = "119.29.137.106";

	static const std::string localhost_url = "127.0.0.1";

	static const int test_royalchen_port = 8989;
	static const std::string test_royalchen_port_str = "8989";

	void onlyQForExit()
	{
		LogDebug("only q will exit,watting.....");
		do
		{
			std::string inputStr;
			getline(std::cin ,inputStr);
			if ( "q" == inputStr )
			{
				break;
			}
		}while ( true );
	}
}
#endif