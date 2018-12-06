// This micro benchmark emulates what happend in AppvIsvSubsystems32.dll
// that is imported by Microsoft Popwerpoint. The first five bytes of
// a Windows API (exported by ntdll, kernel32, ole32, user32, etc.) can be
// replaced by a hooked_API function. 

#pragma warning( disable : 4005)
#include "helper.h"
#include <NTSTATUS.H>

// make realNtClose a global variable as it's delared in AppvIsvSubsystems32.dll
static FARPROC realNtClose;
// a global randomized integer
static int r;

void cpyInt(DWORD startAddr, DWORD dwSize);
void hookedNtClose();

int main(void) {
	// local variables
	HANDLE ghSemaphore;
	HMODULE hNtdll;
	SYSTEM_INFO info;
	DWORD dwPageSize;
	DWORD oldProtect;
	BOOL retVP; 
	BOOL retCH;	
	NTSTATUS status;
	NTSTATUS(*pNtClose) (HANDLE);

	// get page size of current system
	GetSystemInfo(&info);
	dwPageSize = info.dwPageSize;

	// ntdll.dll should be loaded.
	hNtdll = GetModuleHandle(L"ntdll.dll");
	if (!hNtdll)
	{
		printf("ntdll is not loaded --- impossible!");
		exit(1);
	}

	// get function pointer to ntdll::NtClose
	// pNtClose		->	mov eax, 0c
	// pNtClose+5	->	xor ecx, ecx
	//             ...
	pNtClose = (NTSTATUS(*)(HANDLE))GetProcAddress(hNtdll, "NtClose");
	if (!pNtClose)
	{
		printf("GetProcAddress() failed requesting function NtClose()");
		exit(1);
	}

	// allocate memory for realNtClose.
	realNtClose = (FARPROC)VirtualAlloc(NULL, dwPageSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (!realNtClose)
	{
		printf("VirtualAlloc() failed allocating for realNtClose()");
		exit(1);
	}

	// fill the allocated page by 0xCC (INT)
	cpyInt((DWORD)realNtClose, dwPageSize);

	// write realNtClose. 
	// after writing:
	// realNtClose		->	mov eax, 0c		(same to the first 5 bytes of NtClose)
	// realNtClose+5	->	jmp pNtClose+5	(xor ecx, ecx)
	//						INT				(should never executed)
	__asm {
		// copy the first 4 bytes from NtClose (in ntdll) to realNtClose
		mov esi, pNtClose
		mov edi, realNtClose
		mov eax, dword ptr[esi]
		mov dword ptr[edi], eax

		// copy the fifth byte
		add esi, 4
		add edi, 4
		mov al, byte ptr[esi]
		mov byte ptr[edi], al

		// write a jmp instruction at offset 5 of realNtClose	
		inc edi
		mov byte ptr[edi], 0xe9
		mov eax, edi
		add eax, 5
		inc edi
		inc esi
		sub esi, eax
		mov dword ptr[edi], esi
	}

	// make the first 5 bytes of ntdll::NtClose R+W+X
	retVP = VirtualProtect(pNtClose, 5, PAGE_EXECUTE_READWRITE, &oldProtect);
	if (!retVP)
	{
		printf("VirtualProtect() failed on ntdll::NtClose -> R+W+X");
		exit(1);
	}

	// write the fst 5 bytes of ntdll::NtClose to force it jump to hookedNtClose
	// after writing:
	// pNtClose		->	jmp hookedNtClose
	// pNtClose+5	->	xor ecx, ecx
	//             ... 
	__asm {
		mov edi, pNtClose
		mov byte ptr[edi], 0xe9
		mov ecx, hookedNtClose
		mov eax, edi
		inc edi
		add eax, 5
		sub ecx, eax
		mov dword ptr[edi], ecx
	}

	// make the first 5 bytes of ntdll::NtClose E+WriteCopy
	retVP = VirtualProtect(pNtClose, 5, PAGE_EXECUTE_WRITECOPY, &oldProtect);
	if (!retVP)
	{
		printf("VirtualProtect() failed on ntdll::NtClose -> E+WriteCopy");
		exit(1);
	}

	// Create a semaphore and then close the semaphore handle by calling NtClose()
	ghSemaphore = CreateSemaphore(
		NULL,
		1,
		1,
		NULL);

	// initialize seed
	srand((unsigned int)time(NULL));
	// close sematphore handle
	do
	{
		r = rand();
		printf("Trying to close semaphore handle...\n");
		status = pNtClose(ghSemaphore);
	} while (status != STATUS_SUCCESS);

	printf("Semaphore handle closed.\n");

	return 0;
}

void cpyInt(DWORD startAddr, DWORD dwSize)
{
	__asm {
		mov eax, 0xCCCCCCCC
		mov edi, startAddr
		mov ecx, dwSize
		shr ecx, 2
		// this is semanticly equivelent to "rep stosd"
		rep stos dword ptr[edi]
	}
}

// if randomized int r is even -> return STATUS_UNSUCCESSFUL
// r is odd -> jump to realNtClose
__declspec(naked)
void hookedNtClose()
{
	if (r % 2 == 0)
	{
		__asm {
			mov eax, 0xC0000001
			ret
		}
	}

	__asm {
		jmp realNtClose
	}

	printf("Program should not reach here --- impossible!");

	__asm {
		ret
	}
}