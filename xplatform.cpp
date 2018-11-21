#include "helper.h"

static int count_even = 0;
static int count_odd = 0;

NANOSECOND start_time;
NANOSECOND end_time;
NANOSECOND total_time;

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
	start_time = get_wall_time();
	for (int i = 0; i < MAX_lOOP; i++)
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
	end_time = get_wall_time();
	total_time = end_time - start_time;

	// print results
	printf("total time in nanoseconds is %llu\n", (long long unsigned int) total_time);
	printf("%d odd numbers\n", count_odd);
	printf("%d even numbers\n", count_even);

	//getchar();
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
