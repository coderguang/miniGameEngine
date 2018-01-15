#ifndef _DEBUG_TOOL_H_
#define _DEBUG_TOOL_H_

/*
* This file contains several methods to help you debugging your program.
* Collect and Write by : Wangdingqiao
* Create date: 2016-08-19
*/

#include <iostream>
#include <sstream>
#include <stdlib.h>

#ifdef CSG_LINUX 
//Linux code goes here
#include <execinfo.h>
#include <cxxabi.h>
#include <sys/resource.h>
#include <stdio.h>
#elif defined(CSG_WIN)
// windows code goes here
#include <tchar.h>
#include <windows.h>
#include <DbgHelp.h>
#include <psapi.h>
// To ensure correct resolution of symbols, add Psapi.lib to TARGETLIBS
// and compile with -DPSAPI_VERSION=1
// #pragma comment(lib, "psapi.lib")
// #pragma comment(lib, "dbghelp.lib")
#else

#endif


namespace csg
{
	class CDebugToolManager
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

		/*
		* get memory used in bytes, or zero if failed to get info.
		*/
		size_t getMemUsedInBytes() const
		{
			if (!this->_showMemSize)
			{
				return 0;
			}
			else
			{
				return getMemoryUsedInBytes();
			}
		}

		/*
		* get last memory used record according to the last call of setLastLoggedMemSize
		*/
		size_t getLastMemUsedSize() const
		{
			if (!this->_showMemSize)
			{
				return 0;
			}
			return _lastRecordMemSize;
		}

		/*
		* set last memory used record
		* Note: this function should be called whenever you want to trace memory usage
		*/
		void setLastLoggedMemSize(size_t memSize)
		{
			if (!this->_showMemSize)
			{
				return;
			}
			this->_lastRecordMemSize = memSize;
		}

		/*
		* get call stack info
		* @param stakInfo  string to return the stack info
		* @param maxFrameCnt the max frame to get in the call stack
		* @param bShowErrors  whether record the error info when getting call stack
		* @param errLogStream the stream to write error info
		*/
		bool getCallStackInfo(std::string& stackInfo, int maxFrameCnt = 25,
			bool bShowErrors = false, std::ostream& errLogStream = std::cerr) const
		{
			if (!this->_showCallStack)
			{
				return false;
			}
			stackInfo.clear();
			std::stringstream stackStream;
			bool ret = callStackInfo(stackStream, maxFrameCnt, bShowErrors, errLogStream);
			stackInfo = stackStream.str();
			return ret;
		}

		/*
		* just print call stack to stream
		*/
		bool printCallStackInfo(std::ostream& stackStream = std::cout, int maxFrameCnt = 25,
			bool bShowErrors = false, std::ostream& errLogStream = std::cerr) const
		{
			if (!this->_showCallStack)
			{
				return false;
			}
			return callStackInfo(stackStream, maxFrameCnt, bShowErrors, errLogStream);
		}

	private:
		CDebugToolManager() : _lastRecordMemSize(0), _showCallStack(false), _showMemSize(false){}

	private:
		bool _showMemSize;
		size_t _lastRecordMemSize;
		bool _showCallStack;
	private:
		static const int MAX_FRAME_CNT = 63;  // max call stack level
		#ifdef CSG_LINUX 
				//Linux code goes here
				/**
				* used on Linux.
				* Print a demangled stack backtrace of the caller function to streams.
				* reference link: https://panthema.net/2008/0901-stacktrace-demangled/
				*/
				bool callStackInfo(std::ostream& stackStream = std::cout, int maxFrameCnt = 25,
					bool bShowErrors = false, std::ostream& errLogStream = std::cerr) const
				{
					stackStream << "stack trace:" << std::endl;

					// check input
					if (!stackStream || !errLogStream)
					{
						std::cerr << "Error, invalid stream for writing call stack info." << std::endl;
						return false;
					}
					if (bShowErrors && !errLogStream)
					{
						std::cerr << "Error, invalid stream for writing errors." << std::endl;
						return false;
					}
					if (maxFrameCnt <= 0)
					{
						std::cerr << "Error, invalid frame count" << maxFrameCnt << " , must greater than zero." << std::endl;
						return false;
					}
					if (maxFrameCnt > MAX_FRAME_CNT)
					{
						maxFrameCnt = MAX_FRAME_CNT;
					}

					// storage array for stack trace address data
					void* addrlist[MAX_FRAME_CNT];

					// retrieve current stack addresses
					int addrlen = backtrace(addrlist, MAX_FRAME_CNT);

					if (addrlen == 0)
					{
						if (bShowErrors && errLogStream)
						{
							errLogStream << "empty, possibly corrupt ." << std::endl;
						}
						return false;
					}

					// resolve addresses into strings containing "filename(function+address)",
					// this array must be free()-ed
					char** symbollist = backtrace_symbols(addrlist, addrlen);

					// allocate string which will be filled with the demangled function name
					size_t funcnamesize = 256;
					char* funcname = (char*)malloc(funcnamesize);

					// iterate over the returned symbol lines. skip the first, it is the
					// address of this function.
					maxFrameCnt = maxFrameCnt < addrlen ? maxFrameCnt : addrlen;
					for (int i = 2; i < maxFrameCnt; i++)
					{
						char *begin_name = 0, *begin_offset = 0, *end_offset = 0;

						// find parentheses and +address offset surrounding the mangled name:
						// ./module(function+0x15c) [0x8048a6d]
						for (char *p = symbollist[i]; *p; ++p)
						{
							if (*p == '(')
								begin_name = p;
							else if (*p == '+')
								begin_offset = p;
							else if (*p == ')' && begin_offset) 
							{
								end_offset = p;
								break;
							}
						}

						if (begin_name && begin_offset && end_offset
							&& begin_name < begin_offset)
						{
							*begin_name++ = '\0';
							*begin_offset++ = '\0';
							*end_offset = '\0';

							// mangled name is now in [begin_name, begin_offset) and caller
							// offset in [begin_offset, end_offset). now apply
							// __cxa_demangle():

							int status;
							char* ret = abi::__cxa_demangle(begin_name,
								funcname, &funcnamesize, &status);
							if (status == 0) 
							{
								funcname = ret; // use possibly realloc()-ed string
								stackStream << symbollist[i] << ":" << funcname << "+" << begin_offset << std::endl;
							}
							else 
							{
								// demangling failed. Output function name as a C function with
								// no arguments.
								stackStream << symbollist[i] << ":" << begin_name << "+" << begin_offset << std::endl;
							}
						}
						else
						{
							// couldn't parse the line? print the whole line.
							stackStream << symbollist[i] << std::endl;
						}
					}

					free(funcname);
					free(symbollist);

					return true;
				}
				/*
				* used on Linux.
				* get resident  set size (physical memory use)
				* measured in bytes or zero if the value cannot be
				* determined on this OS.
				*/
				size_t getMemoryUsedInBytes() const
				{
					struct rusage r_usage;
					if (getrusage(RUSAGE_SELF, &r_usage) == 0)
					{
						return (size_t)(r_usage.ru_maxrss * 1024L);
					}
					return 0;
				}
		#elif defined(CSG_WIN)
				// windows code goes here
				/*
				* used on windows.
				* print function call stack info
				* Note: For single process only, if used for multiple process, undefined behavior will occurred.
				*/
				bool callStackInfo(std::ostream& stackStream = std::cout,int maxFrameCnt = 25,
					bool bShowErrors = false, std::ostream& errLogStream = std::cerr) const
				{
					stackStream << "stack trace:" << std::endl;
					// check input
					if (!stackStream)
					{
						std::cerr << "Error, invalid stream for writing call stack info." << std::endl;
						return false;
					}
					if (bShowErrors && !errLogStream)
					{
						std::cerr << "Error, invalid stream for writing errors." << std::endl;
						return false;
					}
					if (maxFrameCnt <= 0)
					{
						std::cerr << "Error, invalid frame count: " << maxFrameCnt << " , must greater than zero." << std::endl;
						return false;
					}
					const ULONG SKIP_FRAME_CNT = 2; // skip current function and inner wrapper function
					if (maxFrameCnt > MAX_FRAME_CNT)
					{
						maxFrameCnt = MAX_FRAME_CNT;
					}
					// initialize the Symbol Handler
					DWORD  error;
					HANDLE hProcess;

					SymSetOptions(SYMOPT_UNDNAME | SYMOPT_DEFERRED_LOADS | SYMOPT_LOAD_LINES);

					hProcess = GetCurrentProcess();

					if (!SymInitialize(hProcess, NULL, TRUE))
					{
						// SymInitialize failed
						if (bShowErrors && errLogStream)
						{
							error = GetLastError();
							errLogStream << "SymInitialize returned error :" << error << std::endl;
						}
						
						return false;
					}
					// dynamic get dll function
					typedef USHORT(WINAPI *CaptureStackBackTraceType)(__in ULONG, __in ULONG, __out PVOID*, __out_opt PULONG);
					CaptureStackBackTraceType captureFunc = (CaptureStackBackTraceType)(
						GetProcAddress( LoadLibrary( _T("kernel32.dll")), "RtlCaptureStackBackTrace" ));
					if (captureFunc == NULL)
					{
						if (bShowErrors && errLogStream)
						{
							errLogStream << "Could not get CaptureStackBackTrace function." << std::endl;
						}
						return false;
					}
					// capture stack frames, not dynamic allocate memory
					PVOID  backTraceAddrs[MAX_FRAME_CNT];
					USHORT frameCnt = (captureFunc)(SKIP_FRAME_CNT, MAX_FRAME_CNT, backTraceAddrs, NULL);
					maxFrameCnt = maxFrameCnt < frameCnt ? maxFrameCnt : frameCnt;
					if (maxFrameCnt <= 0)
					{
						if (bShowErrors && errLogStream)
						{
							errLogStream << " Could not get enough frames." << std::endl;
						}
						return false;
					}

					// iterate frames and parse symbol info
					for (USHORT i = 0; i < maxFrameCnt; i++)
					{
						DWORD64  dw64Displacement = 0;
						DWORD64  dwAddress = (DWORD64)backTraceAddrs[i]; // Address you want to check on.

						char buffer[sizeof(SYMBOL_INFO)+MAX_SYM_NAME * sizeof(TCHAR)];
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
							stackStream << maxFrameCnt - i - 1 << "  " << line.FileName << "(" << line.LineNumber << "): ";
						}
						else if (bShowErrors && errLogStream)
						{
							// SymGetLineFromAddr64 failed
							DWORD error = GetLastError();
							errLogStream << "SymGetLineFromAddr64 returned error :" << error << std::endl;
						}

						// get symbol info
						if (SymFromAddr(hProcess, dwAddress, &dw64Displacement, pSymbol))
						{
							// SymFromAddr returned success
							stackStream << "\t" << pSymbol->Name << std::endl;
						}
						else if (bShowErrors && errLogStream)
						{
							// SymFromAddr failed
							DWORD error = GetLastError();
							errLogStream << "SymFromAddr returned error :" << error << std::endl;
						}
					}
					::SymCleanup(::GetCurrentProcess());
					return true;
				}

				/*
				* used on windows.
				* get current work set size or zero when failed to get this info.
				*/
				size_t getMemoryUsedInBytes() const
				{
					HANDLE hProcess;
					PROCESS_MEMORY_COUNTERS pmc;
					hProcess = GetCurrentProcess();
					if (hProcess && GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc)))
					{
						return pmc.WorkingSetSize;
					}
					return 0;
				}
		#else

		#endif
	};
}


#endif