#ifndef _ENGINE_DEF_CSG_DEF_H_
#define _ENGINE_DEF_CSG_DEF_H_

#include <assert.h>


//--------------windows----
#if defined(WIN32)
#define CSG_WIN32
#undef CSG_LINUX
#endif

//abort endian
#if defined(CSG_WIN32) || defined(__i386) || defined(__x86_64)
#define CSG_LITTLE_ENDIAN   1
#endif


//--------------linux------

#ifdef __linux
#define CSG_LINUX
#undef CSG_WIN32
#endif


#ifdef CSG_WIN32
//to support win32
#include <WinSock2.h>
#include <windows.h>
#endif

#ifndef NULL
#define NULL 0
#endif

#ifndef byte_t
typedef unsigned char byte_t;
#endif

#ifndef uint_t
typedef unsigned int uint_t;
#endif

#ifndef ushort_t
typedef unsigned short ushort_t;
#endif

#ifndef size_t
#ifdef CSG_WIN32
typedef unsigned int  size_t;
#elif defined CSG_LINUX
typedef unsigned long  size_t;
#endif
#endif

#ifndef long64_t
#ifdef _WIN32
typedef unsigned __int64 ulong64_t;
typedef __int64 long64_t;
#elif defined __x86_64__
typedef long long64_t;
typedef unsigned long ulong64_t;
#else
typedef long long  long64_t;
typedef unsigned long long ulong64_t;
#endif
#endif


#endif