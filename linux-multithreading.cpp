#include "helper.h"

using namespace std;

static int hChild;
static unsigned long long int trials, hijack_addr;
static volatile int hijacked = 0;

// This function runs the child thread that attempts to hijack the main thread.
// The retaddr_ptr argument points to the main thread's return address slot.
void *ChildThread(void * retaddr_ptr)
{
    printf("Child thread started hijacking.\n");
	// Repeatedly write <hijack_addr> into the main thread's return address slot.
	// The write is attempted <trials> times.
	asm (
		"movq %2, %%rcx\n\t"
		"L : movq %1, (%0)\n\t"
			"loop L" :  : "r" (retaddr_ptr), "r" (hijack_addr), "r" (trials) : "rax", "rbx", "rcx", "memory"
	);

    //*((unsigned long long int *)
    
	// If the hijack was successful, the main thread sets the global "hijacked" variable to 1.
	if (!hijacked)
	{
		printf("All trials complete.  Hijack unsuccessful.\n");
		exit(0);  // The main thread loops infinitely, so to terminate it, we use ExitProcess.
	}
	return 0;
}

int main(int argc, char* argv[])
{
	unsigned int idChild;
    pthread_t thread1;
	void * esp_addr;

	printf("Enter number of trials: ");
	scanf("%llu", &trials);
    
	asm goto (
		"leaq %l2(%%rip), %%rbx\n\t"       // Store the address to which the hijacker should redirect in a global var.
        "movq %%rbx, (%0)\n\t"
		"leaq -8(%%rsp), %%rax\n\t"		// Store the address of the forthcoming return address in esp_addr.
		"movq %%rax, (%1)" : : "r" (&hijack_addr), "r" (&esp_addr) : "rax", "memory" : HIJACK
	);
    
    
	hChild = pthread_create(				    // Spawn the child (hijacker) thread.
        &thread1,
        NULL,
        ChildThread,
        esp_addr);
	
    if (hChild) { 
        printf("Could not make child thread!\n");
        abort();
    }

	// Repeat a guarded return in the tightest possible infinite loop.
    
	asm (
		"leaq L2(%rip), %rbx\n\t"
		"L1 : call L3\n\t"
            "L2 : jmp L1\n\t"
                "L3: ret"
	);

	printf("Infinite loop ended normally---impossible!\n");
	abort();

	// If the hijacker is successful, the "ret" above will jump here.
HIJACK:
	hijacked = 1;
	
    __asm__ (
		"push $0"	// The child thread might still be running, so push a dummy return address for it to continue hijacking.
	);
    
	printf("Hijack successful!\n");
	pthread_join( thread1, NULL);   // Wait for the child thread to terminate normally.
    
	asm (
        "pop %rax"
    );  // Pop the dummy return address.
    
	return 0;
}