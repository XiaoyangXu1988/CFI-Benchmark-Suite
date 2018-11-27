#include "helper.h"
#include "wininet.h"
#include "winnls.h"
#include "shobjidl.h"
#include "objbase.h"
#include "objidl.h"
#include "shlguid.h"
#include "shlobj.h"

//#pragma warning ( disable : 4789 )

NANOSECOND start_time;
NANOSECOND end_time;
NANOSECOND total_time;

// This micro-benchmark is designed to test security, not performance.
int main()
{
	//// record starting time
	//start_time = get_wall_time();

	HRESULT hres;
	IShellLink* pad;

	CoInitialize(NULL);
	hres = CoCreateInstance(CLSID_ActiveDesktop, NULL, CLSCTX_INPROC_SERVER, IID_IActiveDesktop, (LPVOID*)&pad);

	// Calling CoCreateInstance with argument CLSID_ShellLink (exported by shell32.dll) and IID_IShellLink
	// can be dangerous: IShellLink's QueryInterface() is implemented in a way in which it modifies the 
	// "this" pointer (on the stack), and then jumps to the QueryInterface() function that is in its parent's
	// (IUnknown) vtable. Consequently, IUnknown -> AddRef() is called. This CODE-COOP attack can bypass (all?)
	// prior CFI frameworks.
	// hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (LPVOID*)&pad);

	if (SUCCEEDED(hres))
	{
		// function call that leads to buffer overflow
		char buffer[5];
		printf("Write something to a buffer of length 4: ");
		scanf("%s", buffer);

		// QueryInterface() is expected to avoke AddRef() by default. Without proper CFI proction, this 
		// call to QueryInterface() is vulnerable to CODE-COOP attack. 
		IPersistFile* puk;
		hres = pad-> QueryInterface(IID_IUnknown, (LPVOID*)&puk);
		if (SUCCEEDED(hres))
		{
			printf("QueryInterface succeed.\n");
		}
		else
		{
			printf("QueryInterface failed.\n");
		}
	}
	else
	{
		printf("CoCreateInstance failed.\n");
	}

	CoUninitialize();

	//// record ending time
	//end_time = get_wall_time();
	//total_time = end_time - start_time;
	//// print results	
	//printf("total time in nanoseconds is %llu\n", (long long unsigned int) total_time);

	return 0;
}

