#include "memTool.h"
#include <stdio.h>
#include "framework/log/Log.h"

static const int MAX_HEXDUMP_SIZE = 2056;

void csg::CMemToolHelper::hexDump(char *buf, int len, int addr)
{
	if (len > MAX_HEXDUMP_SIZE)
	{
		LogErr(__FUNCTION__ << " too many data,now is " << len << " ,adjust to " << MAX_HEXDUMP_SIZE);
		len = MAX_HEXDUMP_SIZE;
	}

	int i, j, k;
	char binstr[MAX_HEXDUMP_SIZE];
	std::string showMsg="";
	for (i = 0; i < len; i++) {
		if (0 == (i % 16)) { //每16size用 - 分隔
			sprintf(binstr, "%08x -", i + addr);//起始地址
			sprintf(binstr, "%s %02x", binstr, (unsigned char)buf[i]);
		}
		else if (15 == (i % 16)) {
			sprintf(binstr, "%s %02x", binstr, (unsigned char)buf[i]);
			sprintf(binstr, "%s  ", binstr);
			for (j = i - 15; j <= i; j++) {
				sprintf(binstr, "%s%c", binstr, ('!' <= buf[j] && buf[j] <= '~') ? buf[j] : '.');
			}
			showMsg += binstr;
			showMsg += "\n";
		}
		else {
			sprintf(binstr, "%s %02x", binstr, (unsigned char)buf[i]);
		}
	}
	if (0 != (i % 16)) {
		k = 16 - (i % 16);
		for (j = 0; j < k; j++) {
			sprintf(binstr, "%s   ", binstr);//补齐空格
		}
		sprintf(binstr, "%s  ", binstr);
		k = 16 - k;
		for (j = i - k; j < i; j++) {
			sprintf(binstr, "%s%c", binstr, ('!' <= buf[j] && buf[j] <= '~') ? buf[j] : '.');
		}
		showMsg += binstr;
	}
	LogInfo("hexdump:\n" << showMsg);
}

void csg::CMemToolHelper::printTypeSize()
{
	LogDebug(__FUNCTION__ <<"============================ start");

	LogDebug("SIZE_OF_BYTE_T:"<<(int)SIZE_OF_BYTE_T);
	LogDebug("SIZE_OF_INT_T:" << (int)SIZE_OF_INT_T);
	LogDebug("SIZE_OF_SHORT_T:" << (int)SIZE_OF_SHORT_T);
	LogDebug("SIZE_OF_LONG64_T:" << (int)SIZE_OF_LONG64_T);
	LogDebug("SIZE_OF_FLOAT:" << (int)SIZE_OF_FLOAT);
	LogDebug("SIZE_OF_DOUBLE:"<< (int)SIZE_OF_DOUBLE);

	LogDebug(__FUNCTION__ << "============================= end");
}

