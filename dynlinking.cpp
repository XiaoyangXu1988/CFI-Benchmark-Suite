#include "helper.h"

NANOSECOND start_time;
NANOSECOND end_time;
NANOSECOND total_time;

typedef void(*INC)(int&);

int main()
{
	HINSTANCE dllHandle = NULL;
	INC pInc = NULL;
	BOOL retFree = FALSE;
	int count = 0;

	// record starting time
	start_time = get_wall_time();	

	for (int i = 0; i < 50; ++i)
	{
		// load an untrusted module lib.dll
		dllHandle = LoadLibrary(L"lib.dll");
		if (!dllHandle)
		{
			printf("LoadLibrary() failed.\n");
			exit(1);
		}

		// get a function pointer exported by lib.dll
		pInc = (INC)GetProcAddress(dllHandle, "increment");
		if (!pInc)
		{
			printf("GetProcAddress() failed.\n");
			exit(1);
		}

		pInc(count);

		// unload lib.dll
		retFree = FreeLibrary(dllHandle);
		if (!retFree)
		{
			printf("FreeLibrary() failed.\n");
			exit(1);
		}
	}

	// record ending time
	end_time = get_wall_time();
	total_time = end_time - start_time;

	// print results
	printf("total time in nanoseconds is %llu\n", (long long unsigned int) total_time);
	printf("count is %d\n", count);
	return 0;
}