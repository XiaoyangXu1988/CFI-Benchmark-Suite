#include "helper.h"

void JITCallback();

BYTE JIT_code[] = { 
	// prologue
	0x55,			// push ebp
	0x8B, 0xEC,		// mov ebp, esp
	0x53,			// push ebx
	0x56,			// push esi
	0x57,			// push edi

	// call a function in the untrusted module
	0xFF,			
	0x15,			// call ds:[]
	0x00,
	0x00,
	0x00,
	0x00,			// 4 bytes of address need to be patched

	// epilogue
	0x5F,			// pop edi
	0x5E,			// pop esi
	0x8B, 0xE5,		// mov esp, ebp
	0x5D,			// pop ebp
	0xC3			// retn
};

int main()
{
	SYSTEM_INFO info;
	DWORD dwPageSize;
	FARPROC pJIT;
	BOOL retVF;
	   	 	
	// get page size of current system
	GetSystemInfo(&info);
	dwPageSize = info.dwPageSize;

	// allocate a page of memory (RWX)
	pJIT = (FARPROC)VirtualAlloc(NULL, dwPageSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (!pJIT)
	{
		printf("VirtualAlloc() failed allocating pJIT");
		exit(1);
	}

	// patch JIT_code
	void *pJITcallback = &JITCallback;
	void *ppJITcallback = &pJITcallback;
	memcpy(&(JIT_code[8]), &ppJITcallback, sizeof(pJITcallback));

	// copy JIT_code to pJIT
	memcpy(pJIT, JIT_code, sizeof(JIT_code));

	// call pJIT
	pJIT();

	// free the page allocated
	retVF = VirtualFree(pJIT, 0, MEM_RELEASE);
	if (!retVF)
	{
		printf("VirtualFree() failed freeing pJIT");
		exit(1);
	}
	
	return 0;
}

__declspec(naked)
void JITCallback()
{
	// prologue
	__asm {
		push ebp
		mov ebp, esp
		push ebx
		push esi
		push edi
	}

	printf("This is a message in JITCallback()\n");

	// epilogue
	__asm {
		pop edi
		pop esi
		mov esp, ebp
		pop ebp
		ret
	}
}