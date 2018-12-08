// This benchmark should be compiled using VC of versions 
// prior to MSVC++ 14.0 (before VS2015). Since VS2015, 
// there's no longer a library called msvcrxxx.dll, so that 
// there's no __argc as an exported symbol(data).
#include "helper.h"

NANOSECOND start_time;
NANOSECOND end_time;
NANOSECOND total_time;
const int loop_count = MAX_LOOP;

static int arg_count;

int main()
{
	// record starting time
	start_time = get_wall_time();

	for (int i = 0; i < loop_count; ++i)
	{
		// IAT move
		arg_count = __argc;

		// if __argc is not 1, the enfoced CFI framework must have done something.
		if (arg_count != 1)
		{
			printf("arg_count should be 1 (current value: %d).\n", arg_count);
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