#ifndef _FRAMEWORK_TOOL_MEM_TOOL_H_
#define _FRAMEWORK_TOOL_MEM_TOOL_H_

namespace csg {
	
	class CMemToolHelper {
	public:
		static void hexDump(char *buf, int len, int addr);

		static void printTypeSize();
	};


}
#endif