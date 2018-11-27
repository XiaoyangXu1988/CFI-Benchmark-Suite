#include "helper.h"

static HANDLE hChild;
static DWORD trials, hijack_addr;
static volatile int hijacked = 0;

// This function runs the child thread that attempts to hijack the main thread.
// The retaddr_ptr argument points to the main thread's return address slot.
DWORD WINAPI ChildThread(LPVOID retaddr_ptr)
{
	// Repeatedly write <hijack_addr> into the main thread's return address slot.
	// The write is attempted <trials> times.
	_asm {
		mov eax, retaddr_ptr
		mov ebx, hijack_addr
		mov ecx, trials
		L : mov [eax], ebx
			loop L
	}

	// If the hijack was successful, the main thread sets the global "hijacked" variable to 1.
	if (!hijacked)
	{
		printf("All trials complete.  Hijack unsuccessful.\n");
		ExitProcess(0);  // The main thread loops infinitely, so to terminate it, we use ExitProcess.
	}
	return 0;
}

int main(int argc, char* argv[])
{
	DWORD idChild;
	LPVOID esp_addr;

	printf("Enter number of trials: ");
	scanf_s("%u", &trials);

	_asm {
		mov hijack_addr, offset HIJACK  // Store the address to which the hijacker should redirect in a global var.
		lea eax, [esp - 4]				// Store the address of the forthcoming return address in esp_addr.
		mov esp_addr, eax
	}
	hChild = CreateThread(				// Spawn the child (hijacker) thread.
		NULL,
		0,
		ChildThread,
		esp_addr,
		0,
		&idChild);
	if (!hChild) abort();

	// Repeat a guarded return in the tightest possible infinite loop.
	_asm {
		mov eax, offset L2
		L1 : call L3
			 L2 : jmp L1
				  L3 : mov[esp], eax
					   ret
	}

	printf("Infinite loop ended normally---impossible!\n");
	abort();

	// If the hijacker is successful, the "ret" above will jump here.
HIJACK:
	hijacked = 1;
	_asm {
		push 0	// The child thread might still be running, so push a dummy return
				// address for it to continue hijacking.
	}
	printf("Hijack successful!\n");
	WaitForSingleObject(hChild, INFINITE);  // Wait for the child thread to terminate normally.
	_asm { pop eax }  // Pop the dummy return address.
	return 0;
}
