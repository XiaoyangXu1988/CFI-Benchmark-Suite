#include "helper.h"

NANOSECOND start_time;
NANOSECOND end_time;
NANOSECOND total_time;

static int count_0 = 0, count_1 = 0, count_2 = 0;

//callback functions 
void *theadProc0(void *);
void *theadProc1(void *);
void *theadProc2(void *);

int main()
{
    pthread_t threads[3];

	// record starting time
	start_time = get_wall_time();

	// create threads and wait for them to terminate
	for (long long int i = 0; i < MAX_LOOP * LCALTS; i++)
	{
        pthread_create(&threads[0], NULL, &theadProc0, NULL);
        pthread_create(&threads[1], NULL, &theadProc1, NULL);
        pthread_create(&threads[2], NULL, &theadProc2, NULL);
	}

	// record ending time
	end_time = get_wall_time();
	total_time = end_time - start_time;

	// print results
	printf("All threads terminated.\n");	
	printf("total time in nanoseconds is %llu\n", (long long unsigned int) total_time);
	// this call to printf is need so that compiler won't optimize too much
	printf("%d, %d, %d\n", count_0, count_1, count_2);

	pthread_exit(NULL);
}

void *theadProc0(void *)
{
	count_0++;
	pthread_exit(NULL);
}

void *theadProc1(void *)
{
	count_1++;
	pthread_exit(NULL);
}

void *theadProc2(void *)
{
	count_2++;
	pthread_exit(NULL);
}
