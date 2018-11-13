#include "pch.h"
#include <iostream>
#include <windows.h>

int loop_count = USHRT_MAX;

LARGE_INTEGER time_in, time_out, frequency;
__int64 totaltime = 0;
double elapsed_microseconds = 0.0;

int main()
{	
	// record starting time
	QueryPerformanceCounter(&time_in);

	for (int i = 0; i < loop_count; i++)
	{
		printf("This is a message between time_in and time_out\n");
	}

	// record ending time, and calculate running time elapsed in the loop
	QueryPerformanceCounter(&time_out);
	QueryPerformanceFrequency(&frequency);
	totaltime += time_out.QuadPart - time_in.QuadPart;
	elapsed_microseconds = (double)totaltime * 1000000 / frequency.QuadPart;

	// print results
	printf("total time in microseconds is %f\n", elapsed_microseconds);

	return 0;
}
