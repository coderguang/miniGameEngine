#include <iostream>
#include "../util/typetransform.h"
#include "../log/Log.h"
#include "framework/tool/debugTool.h"


using namespace  csg;


void csg::CDebugToolManager::getCurrentStack(std::string &str)
{
#ifdef CSG_WIN
	getCurrentStatckInWin(str);
#elif defined(CSG_LINUX)
	getCurrentStackInLinux(str);
#endif

}


void csg::CDebugToolManager::getCurrentMemInfo(std::string &str)
{
#ifdef CSG_WIN
	getCurrentMemInfoInWin(str);
#elif defined(CSG_LINUX)
	getCurrentMemInfoInLinux(str);
#endif
}

void csg::CDebugToolManager::getCurrentStatckInWin(std::string &info)
{
#ifdef CSG_WIN
	SymSetOptions(SYMOPT_UNDNAME | SYMOPT_DEFERRED_LOADS | SYMOPT_LOAD_LINES);

	DWORD error;
	HANDLE hProcess = GetCurrentProcess();

	std::stringstream sstream;
	sstream << "\n";
	if (!SymInitialize(hProcess, NULL, TRUE)) {
		sstream<<" initialize error \n";
		return;
	}

	// dynamic get dll function
	typedef USHORT(WINAPI *CaptureStackBackTraceType)(__in ULONG, __in ULONG, __out PVOID*, __out_opt PULONG);
	CaptureStackBackTraceType captureFunc = (CaptureStackBackTraceType)(
		GetProcAddress(LoadLibrary(_T("kernel32.dll")), "RtlCaptureStackBackTrace"));
	if (captureFunc == NULL)
	{
		sstream<<"Could not get CaptureStackBackTrace function.\n";
		return;
	}
	PVOID  backTraceAddrs[MAX_FRAME_CNT];
	USHORT frameCnt = (captureFunc)(SKIP_FRAME_CNT, MAX_FRAME_CNT, backTraceAddrs, NULL);
	if (frameCnt <= 0)
	{
		sstream<<"frame less than zero.\n";
		return;
	}

	for (USHORT i = 0; i < frameCnt; i++) {

		DWORD64  dw64Displacement = 0;
		DWORD64  dwAddress = (DWORD64)backTraceAddrs[i]; // Address you want to check on.

		char buffer[sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR)];
		PSYMBOL_INFO pSymbol = (PSYMBOL_INFO)buffer;

		pSymbol->SizeOfStruct = sizeof(SYMBOL_INFO);
		pSymbol->MaxNameLen = MAX_SYM_NAME;

		// get file and line info
		DWORD  dwDisplacement;
		IMAGEHLP_LINE64 line;
		line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);

		if (SymGetLineFromAddr64(hProcess, dwAddress, &dwDisplacement, &line))
		{
			// SymGetLineFromAddr64 returned success
			sstream<<frameCnt - i - 1<<"  "<<line.FileName<<"("<<line.LineNumber<<"): ";
		}
		else
		{
			// SymGetLineFromAddr64 failed
			DWORD error = GetLastError();
			sstream<<"SymGetLineFromAddr64 returned error :"<<error<<"\n";
		}

		// get symbol info
		if (SymFromAddr(hProcess, dwAddress, &dw64Displacement, pSymbol))
		{
			// SymFromAddr returned success
			sstream<< "\t" << pSymbol->Name<<" \n";
		}
		else
		{
			// SymFromAddr failed
			DWORD error = GetLastError();
			sstream<< "SymFromAddr returned error :" << error << std::endl;
		}
	}
	::SymCleanup(::GetCurrentProcess());
	info += sstream.str();
#endif

}

void csg::CDebugToolManager::getCurrentMemInfoInWin(std::string& str)
{
#ifdef CSG_WIN
	HANDLE hProcess;
	PROCESS_MEMORY_COUNTERS pmc;
	hProcess = GetCurrentProcess();
	std::stringstream ss;
	ss << "\n";
	if (hProcess && GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc)))
	{
		ss<<"size:\t"<<pmc.WorkingSetSize<<" byte.\n";
	}
	str += ss.str();
	return ;
#endif

}

void csg::CDebugToolManager::getCurrentMemInfoInLinux(std::string& str)
{
#ifdef CSG_LINUX
	std::stringstream ss;
	ss << "\n";
	struct rusage r_usage;
	if (getrusage(RUSAGE_SELF, &r_usage) == 0)
	{
		ss<<"size:\t"<<(size_t)(r_usage.ru_maxrss * 1024L)<<" byte.\n";
	}
	str += ss.str();
#endif

}

void csg::CDebugToolManager::getCurrentStackInLinux(std::string &info)
{
#ifdef CSG_LINUX
	void *buffer[MAX_FRAME_CNT];
	char **strings;
	int nptrs = backtrace(buffer, MAX_FRAME_CNT);
	std::stringstream sstream;
	sstream << "\n \n";
	sstream<<"\t backtrace() returned "<<nptrs<<" addresses\n";
	strings = backtrace_symbols(buffer, nptrs);
	if (strings == NULL) {
		sstream<<"get stack info failed!\n";
	}
	else
	{
		for (int j = nptrs; j > SKIP_FRAME_CNT; j--) {
			sstream <<j<<"\t"<<strings[nptrs-j+2] << "\n";
		}
		free(strings);
	}
	info += sstream.str();
#endif
}

