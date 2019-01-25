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
#include <stdlib.h> 
#include <limits.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <dlfcn.h>
#include <iostream>
#include <sys/types.h>
#include <pthread.h>
#else
//
#endif

#ifndef FALSE
#define FALSE false
#endif

//#define MAX_LOOP INT_MAX
#define MAX_LOOP 100
#define NANOSECOND uint64_t
#define BILLION 1000000000L

extern NANOSECOND get_wall_time();



