#include "helper.h"

NANOSECOND start_time;
NANOSECOND end_time;
NANOSECOND total_time;

static int count_1 = 0, count_2 = 0, count_3 = 0;

//callback functions 
DWORD WINAPI theadProc1(LPVOID lpParam);
DWORD WINAPI theadProc2(LPVOID lpParam);
DWORD WINAPI theadProc3(LPVOID lpParam);

int main()
{
	HANDLE h1 = 0;
	HANDLE h2 = 0;
	HANDLE h3 = 0;
	HANDLE handles[3];

	// record starting time
	start_time = get_wall_time();

	// create threads and wait for them to terminate
	for (int i = 0; i < MAX_LOOP; i++)
	{
		h1 = CreateThread(NULL, 0, theadProc1, NULL, 0, NULL);
		h2 = CreateThread(NULL, 0, theadProc2, NULL, 0, NULL);
		h3 = CreateThread(NULL, 0, theadProc3, NULL, 0, NULL);

		handles[0] = h1;
		handles[1] = h2;
		handles[2] = h3;

		WaitForMultipleObjects(3, handles, TRUE, INFINITE);

		CloseHandle(h1);
		CloseHandle(h2);
		CloseHandle(h3);
	}

	// record ending time
	end_time = get_wall_time();
	total_time = end_time - start_time;

	// print results
	printf("All threads terminated.\n");	
	printf("total time in nanoseconds is %llu\n", (long long unsigned int) total_time);
	// this call to printf is need so that compiler won't optimize too much
	printf("%d, %d, %d", count_1, count_2, count_3);

	return 0;
}

DWORD WINAPI theadProc1(LPVOID lpParam)
{
	count_1++;
	return 0;
}

DWORD WINAPI theadProc2(LPVOID lpParam)
{
	count_2++;
	return 0;
}

DWORD WINAPI theadProc3(LPVOID lpParam)
{
	count_3++;
	return 0;
}
