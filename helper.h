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
#else
//
#endif

#define MAX_lOOP INT_MAX
#define NANOSECOND uint64_t
#define BILLION 1000000000L

extern NANOSECOND get_wall_time();



