#include "pch.h"
#include <iostream>
#include <windows.h>

LONGLONG factorial(int n);
LONGLONG helper(int n, int result);

// calculate factorial of n
int n = 10;
LONGLONG sum = 0;
LONGLONG val = 0;
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
		val = factorial(n);
	}

	// record ending time, and calculate running time elapsed in the loop
	QueryPerformanceCounter(&time_out);
	QueryPerformanceFrequency(&frequency);
	totaltime += time_out.QuadPart - time_in.QuadPart;
	elapsed_microseconds = (double)totaltime * 1000000 / frequency.QuadPart;

	// print results
	printf("total time in microseconds is %f\n", elapsed_microseconds);
	printf("factorial of %d is %lld\n", n, val);
	printf("sum is %lld\n", sum);
	return 0;
}

LONGLONG factorial(int n)
{
	// calculate factorial of a positive integer
	if (n <= 0)
		return -1;

	// non-tail call to hepler
	// this is needed so that compiler won't optimize 
	// too much
	for (int i = 1; i < n; i++)
	{
		LONGLONG val = helper(i, 1);
		sum += val;
	}

	// tail call to helper function
	return helper(n, 1);
}

LONGLONG helper(int n, int result)
{
	// base case
	if (n == 1)
		return result;
	
	// tail-recursive. This call should be optimized 
	// by compiler to concitional jumps
	return helper(n - 1, result * n);
}
