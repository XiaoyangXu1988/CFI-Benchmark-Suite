#include "helper.h"

#ifdef _WIN32

NANOSECOND get_wall_time()
{
	LARGE_INTEGER time, frequency;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&time);
	return (NANOSECOND)(time.QuadPart * BILLION / frequency.QuadPart);
}

#elif __linux__

NANOSECOND get_wall_time()
{
	struct timespec time;
	clock_gettime(CLOCK_MONOTONIC, &time);
	return (NANOSECOND)(BILLION * time.tv_sec + time.tv_nsec);
}

#else
//
#endif