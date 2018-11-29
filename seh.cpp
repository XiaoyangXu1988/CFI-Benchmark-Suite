#include "helper.h"

void writeToMem();

NANOSECOND start_time;
NANOSECOND end_time;
NANOSECOND total_time;

static int except_count = 0;
static int finally_count = 0;

int main()
{
	// record starting time
	start_time = get_wall_time();	

	for (int i = 0; i < 40; ++i)
	{
		__try
		{
			writeToMem();
		}
		__except (GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION ?
			EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
		{
			except_count++;
		}
	}

	// record ending time
	end_time = get_wall_time();
	total_time = end_time - start_time;

	// print results
	printf("total time in nanoseconds is %llu\n", (long long unsigned int) total_time);
	printf("except_count is %d\nfinally_count is %d\n ", except_count++, finally_count);

	return 0;
}

void writeToMem()
{
	__try
	{
		__try
		{
			__asm {
				mov eax, 0
				mov [eax], 0
			}
		}
		__finally
		{
			finally_count++;
		}
	}
	__except (GetExceptionCode() == EXCEPTION_FLT_DIVIDE_BY_ZERO ?
		EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
	{
		printf("This should not be printed --- impossible!\n");
	}
}