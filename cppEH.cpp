#include "helper.h"

void throwInt();

NANOSECOND start_time;
NANOSECOND end_time;
NANOSECOND total_time;

static int main_catch_count = 0;
static int throwInt_catch_count = 0;
const static int loop_count = 10000L;

int main()
{
	// record starting time
	start_time = get_wall_time();

	for (int i = 0; i < loop_count; ++i)
	{
		try
		{
			throwInt();
		}
		catch (int e)
		{
			main_catch_count++;
		}
	}

	// record ending time
	end_time = get_wall_time();
	total_time = end_time - start_time;

	// print results
	printf("total time in nanoseconds is %llu\n", (long long unsigned int) total_time);
	printf("main_catch_count is %d\nthrowInt_catch_count is %d\n ", main_catch_count++, throwInt_catch_count);

	return 0;
}

void throwInt()
{
	try
	{
		throw 7;
	}
	catch (bool e)
	{
		throwInt_catch_count++;
	}
}