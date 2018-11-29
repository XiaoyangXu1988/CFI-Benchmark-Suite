#include "helper.h"

NANOSECOND start_time;
NANOSECOND end_time;
NANOSECOND total_time;
const int loop_count = 10000L;

int main()
{
	LPVOID base_addr = NULL;
	DWORD dwOldProtect;
	BOOL retVP = FALSE;
	BOOL retVF = FALSE;
	SIZE_T dwSize = 1;

	// record starting time
	start_time = get_wall_time();	

	for (int i = 0; i < loop_count; ++i)
	{
		base_addr = VirtualAlloc(
			NULL,
			dwSize,
			MEM_COMMIT,
			PAGE_READWRITE
		);
		
		if (!base_addr)
		{
			printf("VirtualAlloc() failed...\n");
			exit(1);
		}

		retVP = VirtualProtect(
			base_addr,
			dwSize,
			PAGE_READONLY,
			&dwOldProtect
		);

		if (!retVP)
		{
			printf("VirtualProtect() failed...\n");
			exit(1);
		}

		retVF = VirtualFree(
			base_addr,
			0,
			MEM_RELEASE
		);

		if (!retVF)
		{
			printf("VirtualFree() failed...\n");
			exit(1);
		}
	}

	// record ending time
	end_time = get_wall_time();
	total_time = end_time - start_time;

	// print results
	printf("total time in nanoseconds is %llu\n", (long long unsigned int) total_time);
	return 0;
}
