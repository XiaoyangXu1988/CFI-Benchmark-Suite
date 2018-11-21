#include "helper.h"

static int count_even = 0;
static int count_odd = 0;

NANOSECOND start_time;
NANOSECOND end_time;
NANOSECOND total_time;

int main()
{
	// declare a function pointer, so that each call 
	// via this pointer would be a indirect call
	void(*fptr) (int n);

	// initialize random seed
	srand((unsigned int)time(NULL));
	// record starting time
	start_time = get_wall_time();

	// Activity to be timed
	for (int i = 0; i < MAX_lOOP; i++)
	{
		// printf is a IAT function call.
		printf("This is a message between start_time and end_time\n");
	}

	// record ending time, and calculate running time elapsed in the loop
	end_time = get_wall_time();
	total_time = end_time - start_time;

	// print results
	printf("total time in nanoseconds is %llu\n", (long long unsigned int) total_time);
	//getchar();
	return 0;
}
