#include "helper.h"

void JITCALLBACKPTR();

typedef void (*CALLBACKPTR)();
//typedef void(*INC)(int&);

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
	0x5b,           // pop ebx
	0x8B, 0xE5,		// mov esp, ebp
	0x5D,			// pop ebp
	0xC3			// retn
};

int main()
{

	#ifdef _WIN32	   	 	
	SYSTEM_INFO info;
	DWORD dwPageSize;
	FARPROC pJIT;
	BOOL retVF;
	
	// get page size of current system
	GetSystemInfo(&info);
	dwPageSize = info.dwPageSize;
	
	// allocate a page of memory (RWX)
    pJIT = (FARPROC)VirtualAlloc(NULL, dwPageSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

    #elif __linux__    
    uint8_t *pJIT;
    int page_size;
    int fd;
    
    page_size = getpagesize();

	// allocate a page of memory (RWX)
	
	fd = open ("/dev/zero", O_RDONLY);
	pJIT = (uint8_t *) mmap (NULL, page_size, PROT_READ | PROT_WRITE | PROT_EXEC , MAP_PRIVATE, fd, 0);
	#endif
	
	if (!pJIT)
	{
		printf("Memory allocation failed for pJIT");
		exit(1);
	}

	// patch JIT_code
	CALLBACKPTR pJITCALLBACKPTR = &JITCALLBACKPTR;
	void *ppJITCALLBACKPTR = &pJITCALLBACKPTR;
	memcpy(&(JIT_code[8]), &ppJITCALLBACKPTR, sizeof(pJITCALLBACKPTR));

	// copy JIT_code to pJIT
	memcpy(pJIT, JIT_code, sizeof(JIT_code));

	// call pJIT
	((CALLBACKPTR) pJIT)();

	// free the page allocated
	#ifdef _WIN32
	retVF = VirtualFree(pJIT, 0, MEM_RELEASE);
	if (!retVF)
	{
		printf("VirtualFree() failed freeing pJIT");
		exit(1);
	}
	#elif __linux__
	munmap(pJIT, page_size);
	#endif
	
	return 0;
}

#ifdef _WIN32
__declspec(naked)
#endif
void JITCALLBACKPTR()
{
	printf("This is a message in JITCALLBACKPTR()\n");
}
