#include "helper.h"

LONGLONG factorial(int n);
LONGLONG fac_helper(int n, int result);

// calculate factorial of n
int n = 10;
LONGLONG sum = 0;
LONGLONG val = 0;

NANOSECOND start_time;
NANOSECOND end_time;
NANOSECOND total_time;

int main()
{
	// record starting time
	start_time = get_wall_time();

	for (int i = 0; i < MAX_lOOP; i++)
	{
		val = factorial(n);
	}

	// record ending time, and calculate running time elapsed in the loop
	end_time = get_wall_time();
	total_time = end_time - start_time;

	// print results
	printf("total time in nanoseconds is %llu\n", (long long unsigned int) total_time);
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
		LONGLONG val = fac_helper(i, 1);
		sum += val;
	}

	// tail call to fac_helper function
	return fac_helper(n, 1);
}

LONGLONG fac_helper(int n, int result)
{
	// base case
	if (n == 1)
		return result;
	
	// tail-recursive. This call should be optimized 
	// by compiler to concitional jumps
	return fac_helper(n - 1, result * n);
}
