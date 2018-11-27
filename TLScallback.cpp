#include "helper.h"

void NTAPI TLSEntry(PVOID DllHandle, DWORD dwReason, PVOID);
DWORD WINAPI ThreadProc(CONST LPVOID lpParam);

#ifdef _WIN32
#pragma comment (linker, "/INCLUDE:__tls_used")
#pragma comment (linker, "/INCLUDE:_tls_callback")
#else
#pragma comment (linker, "/INCLUDE:_tls_used")
#pragma comment (linker, "/INCLUDE:tls_callback")
#endif  
#ifdef _WIN32
#pragma data_seg(".CRT$XLF")
EXTERN_C
#else
#pragma const_seg(".CRT$XLF")
EXTERN_C const
#endif
PIMAGE_TLS_CALLBACK tls_callback = TLSEntry;
#ifdef _WIN32
#pragma data_seg()
#else
#pragma const_seg()
#endif //_WIN32

NANOSECOND start_time;
NANOSECOND end_time;
NANOSECOND total_time;

int main()
{
	const int thread_count = 10;
	HANDLE handles[thread_count];

	// record starting time
	start_time = get_wall_time();

	for (int i = 0; i < thread_count; i++)
	{
		handles[i] = CreateThread(NULL, 0, &ThreadProc, 0, 0, NULL);
	}
	WaitForMultipleObjects(thread_count, handles, TRUE, INFINITE);

	for (int i = 0; i < thread_count; i++)
	{
		CloseHandle(handles[i]);
	}

	// record ending time, and calculate running time elapsed in the loop
	end_time = get_wall_time();
	total_time = end_time - start_time;

	// print results
	printf("total time in nanoseconds is %llu\n", (long long unsigned int) total_time);
	return 0;
}

DWORD WINAPI ThreadProc(CONST LPVOID lpParam)
{
	ExitThread(0);
}

void NTAPI TLSEntry(PVOID DllHandle, DWORD dwReason, PVOID)
{
	if (dwReason == DLL_THREAD_ATTACH)
	{
		printf("DLL_THREAD_ATTACH\n");
	}

	if (dwReason == DLL_THREAD_DETACH)
	{
		printf("DLL_THREAD_DETACH\n");
	}

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		printf("DLL_PROCESS_ATTACH\n");
	}

	if (dwReason == DLL_PROCESS_DETACH)
	{
		printf("DLL_PROCESS_DETACH\n");
	}
}
