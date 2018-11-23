#include "helper.h"

NANOSECOND start_time;
NANOSECOND end_time;
NANOSECOND total_time;

//A function does nothing but return
void retFunc();

// call virtual functions in an intensive loop
int main()
{
	// record starting time
	start_time = get_wall_time();

	for (int i = 0; i < MAX_lOOP; i++)
	{
		retFunc();
	}

	// record ending time, and calculate running time elapsed in the loop
	end_time = get_wall_time();
	total_time = end_time - start_time;

	// print results
	printf("total time in nanoseconds is %llu\n", (long long unsigned int) total_time);

	return 0;
}

__declspec(naked)
void retFunc()
{
	__asm { ret }
}