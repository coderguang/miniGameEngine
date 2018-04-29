
#ifndef _FRAMEWORK_TOOL_DEBUG_TOOL_H_
#define _FRAMEWORK_TOOL_DEBUG_TOOL_H_


#ifdef CSG_LINUX
#include <execinfo.h>
#include <cxxabi.h>
#include <sys/resource.h>
#elif defined(CSG_WIN)
#include <windows.h>
#include <imagehlp.h>
#include <tchar.h>
#include <psapi.h>

// 需要在项目链接器---输入--附加依赖项中 加入 "Imagehlp.lib"

#endif

#include "../DesignPattern/Singleton.h"


namespace csg
{
	class CDebugToolManager:public Singleton<CDebugToolManager>
	{
	public:
		static CDebugToolManager* instance()
		{
			static CDebugToolManager* inst = new CDebugToolManager();
			return inst;
		}
		void setOptions(bool bShowMemSize = true, bool bShowCallStack = true)
		{
			this->_showMemSize = bShowMemSize;
			this->_showCallStack = bShowCallStack;
		}
		void setShowMemSize(bool bShow)
		{
			this->_showMemSize = bShow;
		}
		bool isShowMemSize() const
		{
			return this->_showMemSize;
		}
		void setShowCallStack(bool bShow)
		{
			this->_showCallStack = bShow;
		}
		bool isShowCallStack() const
		{
			return this->_showCallStack;
		}

		void getCurrentStack(std::string &str);

		void getCurrentMemInfo(std::string &str);

	protected:
		void getCurrentStackInLinux(std::string &str);

		void getCurrentStatckInWin(std::string &str);

		void getCurrentMemInfoInWin(std::string& str);

		void getCurrentMemInfoInLinux(std::string& str);


	private:
		CDebugToolManager() : _lastRecordMemSize(0), _showCallStack(false), _showMemSize(false){}

	private:
		bool _showMemSize;
		size_t _lastRecordMemSize;
		bool _showCallStack;
	private:
		static const int MAX_FRAME_CNT = 63;  // max call stack level
		static const int SKIP_FRAME_CNT = 2; // ignore this class function
	};
}


#endif