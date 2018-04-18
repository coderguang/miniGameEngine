#ifndef _FRAMEWORK_UTIL_SYS_UTIL_H_
#define _FRAMEWORK_UTIL_SYS_UTIL_H_

#include <string>

namespace csg
{
	class CSysUtil
	{
	public:
		//��ȡ����
		static int getNumberOfProcessors();
		//��ȡ�ϴδ�����--�����ڴ�����ʱ��������,������;�ᱻ������������
		static unsigned long getLastError();

		static void recordErrorCode(std::string info);
	};
#define CSG_RECORD_ERROR(X) CSysUtil::recordErrorCode(X)
}
#endif