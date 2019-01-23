#include "helper.h"

static int zero_count = 0;
static int one_count = 0;
static int two_count = 0;
static int three_count = 0;
const int divisor = 4;

NANOSECOND start_time;
NANOSECOND end_time;
NANOSECOND total_time;

int main()
{
	srand((unsigned int)time(NULL));
	int dividend = 0;
	int remainder = 0;

	start_time = get_wall_time();

	for (int i = 0; i < MAX_LOOP; i++)
	{
		dividend = rand();
		remainder = dividend % divisor;

		switch (remainder)
		{
		case 0:
			zero_count += 1;
			break;
		case 1:
			one_count += 1;
			break;
		case 2:
			two_count += 1;
			break;
		case 3:
			three_count += 1;
			break;
		default:
			printf("should not reach here -- impossible!");
		}
	}

	end_time = get_wall_time();
	total_time = end_time - start_time;

	// print results
	printf("total time in nanoseconds is %llu\n", (long long unsigned int) total_time);
	printf("%d numbers have remainder of zero modulo %d.\n", zero_count, divisor);
	printf("%d numbers have remainder of one modulo %d.\n", one_count, divisor);
	printf("%d numbers have remainder of two modulo %d.\n", two_count, divisor);
	printf("%d numbers have remainder of three modulo %d.\n", three_count, divisor);

	return 0;
}