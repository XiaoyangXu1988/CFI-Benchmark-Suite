#include "helper.h"

#ifdef _WIN32

NANOSECOND get_wall_time()
{
    LARGE_INTEGER time, frequency;
    
    // We now have the elapsed number of ticks, along with the
    // number of ticks-per-second. We use these values
    // to convert to the number of elapsed microseconds.
    // To guard against loss-of-precision, we convert
    // to microseconds *before* dividing by ticks-per-second.
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
