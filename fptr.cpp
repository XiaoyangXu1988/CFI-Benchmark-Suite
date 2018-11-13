#include "pch.h"
#include <iostream>
#include <time.h> 
#include <windows.h>

int loop_count = USHRT_MAX;
static int count_even = 0;
static int count_odd = 0;

LARGE_INTEGER time_in, time_out, frequency;
__int64 totaltime = 0;
double elapsed_microseconds = 0.0;

// declare two functions with same signature
void printEven(int n);
void printOdd(int n);

int main()
{	
	// declare a function pointer, so that each call 
	// via this pointer would be a indirect call
	void(*fptr) (int n);	

	// initialize random seed
	srand((unsigned int)time(NULL));
	// record starting time
	QueryPerformanceCounter(&time_in);
	
	for (int i = 0; i < loop_count; i++)
	{
		// depend on parity of randomized number, call
		// different function using function pointer
		int r = rand();
		if (r % 2 == 0)
			fptr = printEven;
		else
			fptr = printOdd;
		fptr(r);
	}

	// record ending time, and calculate running time elapsed in the loop
	QueryPerformanceCounter(&time_out);
	QueryPerformanceFrequency(&frequency);
	totaltime += time_out.QuadPart - time_in.QuadPart;
	elapsed_microseconds = (double)totaltime * 1000000 / frequency.QuadPart;

	// print results
	printf("total time in microseconds is %f\n", elapsed_microseconds);

	printf("%d odd numbers\n", count_odd);
	printf("%d even numbers\n", count_even);

	return 0;
}

void printEven(int n)
{
	count_even++;
}

void printOdd(int n)
{
	count_odd++;
}