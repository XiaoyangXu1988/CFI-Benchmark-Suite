#include "pch.h"
#include <iostream>
#include <windows.h>

int loop_count = USHRT_MAX;

LARGE_INTEGER start_time, end_time, elapsed_microseconds;
LARGE_INTEGER frequency;

int main()
{	
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start_time);

	// Activity to be timed
	for (int i = 0; i < loop_count; i++)
	{
		// printf is a IAT function call.
		printf("This is a message between start_time and end_time\n");
	}

	QueryPerformanceCounter(&end_time);
	elapsed_microseconds.QuadPart = end_time.QuadPart - start_time.QuadPart;
	
	// We now have the elapsed number of ticks, along with the
	// number of ticks-per-second. We use these values
	// to convert to the number of elapsed microseconds.
	// To guard against loss-of-precision, we convert
	// to microseconds *before* dividing by ticks-per-second.
	elapsed_microseconds.QuadPart *= 1000000;
	elapsed_microseconds.QuadPart /= frequency.QuadPart;

	// print results
	printf("total time in microseconds is %I64d\n", elapsed_microseconds.QuadPart);

	return 0;
}
