#include "helper.h"

static int count_even = 0;
static int count_odd = 0;

void randAndCount();
void countEven(int n);
void countOdd(int n);

int main()
{
	srand((unsigned int)time(NULL));	
	for (int i = 0; i < MAX_LOOP; i++)
	{
		randAndCount();
	}

	printf("%d odd numbers\n", count_odd);
	printf("%d even numbers\n", count_even);

	return 0;
}

void randAndCount()
{
	void(*fptr) (int n);
	int r = rand();

	if (r % 2 == 0)
	{
		fptr = countEven;
	}
	else
	{
		fptr = countOdd;
	}

	fptr(r);
}

void  countEven(int n)
{
	count_even++;
}

void countOdd(int n)
{
	count_odd++;
}
