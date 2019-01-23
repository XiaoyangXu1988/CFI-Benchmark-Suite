#include "helper.h"

static int zero_count = 0;
static int one_count = 0;
static int two_count = 0;
static int three_count = 0;
const int divisor = 4;

NANOSECOND start_time;
NANOSECOND end_time;
NANOSECOND total_time;

void helper();
void case0();
void case1();
void case2();
void case3();

int main()
{
srand((unsigned int)time(NULL));
start_time = get_wall_time();

for (int i = 0; i < MAX_LOOP; i++)
{
helper();
}

end_time = get_wall_time();
total_time = end_time - start_time;

printf("total time in nanoseconds is %llu\n", (long long unsigned int) total_time);
printf("%d numbers have remainder of zero modulo %d.\n", zero_count, divisor);
printf("%d numbers have remainder of one modulo %d.\n", one_count, divisor);
printf("%d numbers have remainder of two modulo %d.\n", two_count, divisor);
printf("%d numbers have remainder of three modulo %d.\n", three_count, divisor);
}

void helper()
{
void(*fptr) ();
int r = rand();
int remainder = r % divisor;

if (remainder == 0)
fptr = case0;
if (remainder == 1)
fptr = case1;
if (remainder == 2)
fptr = case2;
if (remainder == 3)
fptr = case3;

fptr();
}

void case0()
{
zero_count += 1;
}

void case1()
{
one_count += 1;
}

void case2()
{
two_count += 1;
}

void case3()
{
three_count += 1;
}
