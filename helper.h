#pragma once

//include different header files
#ifdef _WIN32
#include <iostream>
#include <windows.h>
#include <time.h>
#include <random>
#elif __linux__
#include <iostream>
#include <time.h>
#include <stdio.h> 
#include <limits.h>
#include <stdint.h>
#include <cstdlib>
#include <dlfcn.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <stdarg.h>
#define FALSE false
#define BYTE unsigned char
#else
//
#endif

#define MAX_LOOP 1048576
#define NANOSECOND uint64_t
#define BILLION 1000000000L

extern NANOSECOND get_wall_time();

#ifdef _WIN32
#define CDECL __cdecl
#define STDCALL __stdcall
#define FASTCALL __fastcall
#define THISCALL __thiscall
#elif __linux__
#define CDECL __attribute__((cdecl))
//#define STDCALL __attribute__((stdcall))
#define STDCALL
#define FASTCALL __attribute__((fastcall))
#define THISCALL __attribute__((thiscall))
#else
//
#endif
