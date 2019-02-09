#include "helper.h"
#include "inc.h"

NANOSECOND start_time;
NANOSECOND end_time;
NANOSECOND total_time;

int main()
{
	int imp_null = -1;

	// record starting time
	start_time = get_wall_time();

	for (long long int i = 0; i < MAX_LOOP * IMPDTS; ++i)
	{
		// IAT data movement
		imp_null = (int) exp_null;

		// if imp_null is not NULL, the enfoced CFI framework must have done something.
		if (imp_null != 0)
		{
			printf("imp_null should be NULL (current value: %d).\n", imp_null);
			exit(1);
		}
	}

	// record ending time
	end_time = get_wall_time();
	total_time = end_time - start_time;

	// print results
	printf("total time in nanoseconds is %llu\n", (long long unsigned int) total_time);

	return 0;
}
