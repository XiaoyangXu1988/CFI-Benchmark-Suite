#include "helper.h"

void JITCALLBACKPTR();

typedef void (*CALLBACKPTR)();
//typedef void(*INC)(int&);

BYTE JIT_code[] = { 
	// prologue
	0x55,			// push ebp/rbp
	0x48,           // dec  eax if compiled for 32bit otherwise extend ebp and esp to rbp and rsp for next ins
	0x8B, 0xEC,		// mov  ebp, esp
	0x53,			// push ebx/rbx
	0x56,			// push esi/rsi
	0x57,			// push edi/rdi

	// computed call to a function in the untrusted module
	0x48,           // dec  eax if compiled for 32bit otherwise extend ebx to rbx for next ins
	0xbb,			// mov  ebx, 0x00000000
	0x00,
	0x00,
	0x00,
	0x00,
	0x90,
	0x90,
	0x90,
	0x90,			// 8 bytes of address need to be patched -- NOP is added so that it works for both 32-bit and 64-bit machine
	0xff, 0x13,     // call ptr [ebx/rbx]

	// epilogue
	0x5F,			// pop edi/rdi
	0x5E,			// pop esi/rsi
	0x5b,           // pop ebx/rbx
	0x48,           // dec  eax if compiled for 32bit otherwise extend ebp and esp to rbp and rsp for next ins
	0x8B, 0xE5,		// mov esp, ebp
	0x5D,			// pop ebp/rbp
	0xC3			// retn
};

NANOSECOND start_time;
NANOSECOND end_time;
NANOSECOND total_time;

long long int flag = 0;

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
	memcpy(&(JIT_code[9]), &ppJITCALLBACKPTR, sizeof(pJITCALLBACKPTR));

	// copy JIT_code to pJIT
	memcpy(pJIT, JIT_code, sizeof(JIT_code));

	// record starting time
	start_time = get_wall_time();

    // call pJIT several times to see the overhead of guarding it if any
    for (; flag < MAX_LOOP * JITCTS; flag++)
	    ((CALLBACKPTR) pJIT)();
	
	// record ending time, and calculate running time elapsed in the loop
	end_time = get_wall_time();
	total_time = end_time - start_time;
	
	printf("total time in nanoseconds is %llu\n", (long long unsigned int) total_time);

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

void JITCALLBACKPTR()
{
    if(!flag)
    	printf("This is a message in JITCALLBACKPTR()\n");
}
