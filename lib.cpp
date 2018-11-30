#include <stdio.h>
#include <Windows.h>

BOOL APIENTRY DllMain(
	HANDLE hModule,	   // Handle to DLL module 
	DWORD ul_reason_for_call,
	LPVOID lpReserved)     // Reserved
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		// A process is loading the DLL.
		break;

	case DLL_THREAD_ATTACH:
		// A process is creating a new thread.
		break;

	case DLL_THREAD_DETACH:
		// A thread exits normally.
		break;

	case DLL_PROCESS_DETACH:
		// A process unloads the DLL.
		break;
	}
	return TRUE;
}

extern "C" __declspec(dllexport)
void increment(int &i)
{
	if (i < INT_MAX)
	{
		i++;
	}
	return;
}

