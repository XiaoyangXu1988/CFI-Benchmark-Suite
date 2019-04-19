#include "helper.h"

int IntSum(int count, ...);
double DoubleSum(int count, ...);

int main()
{
	int intSum_ans = 0;
	intSum_ans = IntSum(16, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
	//printf("IntSum: sum is %d\n", intSum_ans);
	
	double doubleSum_ans = 0.0;
	doubleSum_ans = DoubleSum(16, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16);
	//printf("DoubleSum: sum is %f\n", doubleSum_ans);

	//if ((intSum_ans == 136))
	if ((intSum_ans == 136) && (doubleSum_ans - 141.41 <= 0.000000000001))
	{
		printf("Sums correctly cuculated!\n");
		return 0;
	}
	else
	{
		printf("Sums incorrect!\n");
		return -1;
	}
}

int IntSum(int count, ...)
{
	va_list ap;
	int sum = 0;

	va_start(ap, count);
	for (int i = 0; i < count; i++)
		sum += va_arg(ap, int);
	va_end(ap);

	return sum;
}

double DoubleSum(int count, ...)
{
	va_list ap;
	double sum = 0.0;
	double next = 0.0;

	va_start(ap, count);
	for (int i = 0; i < count; i++)
		sum += va_arg(ap, double);
	va_end(ap);

	return sum;
}