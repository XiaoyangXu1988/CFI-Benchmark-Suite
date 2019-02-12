#include "helper.h"

NANOSECOND start_time;
NANOSECOND end_time;
NANOSECOND total_time;

LONG WINAPI VectoredHandlerSkip(struct _EXCEPTION_POINTERS *ExceptionInfo);

int main()
{
    DWORD loop_count = 10000L;
    PVOID pv = NULL;

    // record starting time
    start_time = get_wall_time();    

    // Register a vectored exception handler
    pv = AddVectoredExceptionHandler(0, VectoredHandlerSkip);

    // Triger a hardware exception by writing to DS:[0]
    __asm {
        mov eax, 0
        mov ecx, loop_count
        L : mov [eax], 0
            loop L
    }

    // Remove the vectored exception handler
    RemoveVectoredExceptionHandler(pv);

    // record ending time
    end_time = get_wall_time();
    total_time = end_time - start_time;

    // print results
    printf("total time in nanoseconds is %llu\n", (long long unsigned int) total_time);

    return 0;
}

LONG WINAPI
VectoredHandlerSkip(struct _EXCEPTION_POINTERS *ExceptionInfo)
{
    PCONTEXT Context;    
    Context = ExceptionInfo->ContextRecord;
    // The instruction "mov [eax], 0" has length of 3, eip += 3 will redirect 
    // the control flow to the next "loop L" instruction.
    Context->Eip = Context->Eip + 3;
    return EXCEPTION_CONTINUE_EXECUTION;
}