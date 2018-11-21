#include "helper.h"

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

NANOSECOND start_time;
NANOSECOND end_time;
NANOSECOND total_time;

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
	start_time = get_wall_time();

	for (int i = 0; i < MAX_lOOP; i++)
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
	end_time = get_wall_time();
	total_time = end_time - start_time;
	
	// print results
	printf("total time in nanoseconds is %llu\n", (long long unsigned int) total_time);
	printf("%d odd numbers\n", pn->count_odd);
	printf("%d even numbers\n", pn->count_even);

	return 0;
}
