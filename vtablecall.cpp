#include "pch.h"
#include <iostream>
#include <time.h> 
#include <windows.h>

/* Base class */
class number
{
public:
	int count_even = 0;
	int count_odd = 0;

	virtual int random() { return 0;  };
	virtual void accEven() {};
	virtual void accOdd() {};
	virtual bool isOdd(int) { return FALSE;  };
};

/* Derived class */
class parity: public number
{
public:
	int random()
	{
		return rand();
	}

	void accEven()
	{
		count_even++;
	}

	void accOdd()
	{
		count_odd++;
	}

	bool isOdd(int n)
	{
		return (n % 2);
	}
};

int loop_count = USHRT_MAX;

LARGE_INTEGER time_in, time_out, frequency;
__int64 totaltime = 0;
double elapsed_microseconds = 0.0;

// call virtual functions in an intensive loop
int main()
{	
	int n;
	// define a derived class instance and a pointer
	// that has type of base class
	parity p;
	number *pn = &p;	

	// initialize random seed
	srand((unsigned int)time(NULL));
	// record starting time
	QueryPerformanceCounter(&time_in);

	for (int i = 0; i < USHRT_MAX; i++)
	{
		n = pn->random();
		if (pn->isOdd(n))
		{
			pn->accOdd();
		}
		else
		{
			pn->accEven();
		}
	}

	// record ending time, and calculate running time elapsed in the loop
	QueryPerformanceCounter(&time_out);
	QueryPerformanceFrequency(&frequency);
	totaltime += time_out.QuadPart - time_in.QuadPart;
	elapsed_microseconds = (double)totaltime * 1000000 / frequency.QuadPart;
	
	// print results
	printf("total time in microseconds is %f\n", elapsed_microseconds);
	printf("%d odd numbers\n", pn->count_odd);
	printf("%d even numbers\n", pn->count_even);

	return 0;
}