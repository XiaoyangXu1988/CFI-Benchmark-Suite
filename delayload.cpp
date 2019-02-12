// This macro-benchmark should be compiled by Microsoft Visual Studio
// with additional linker option /DELAYLOAD:"user32.dll", so that
// user32.dll would be delay loaded.

#include "helper.h"

NANOSECOND start_time;
NANOSECOND end_time;
NANOSECOND total_time;

int main()
{    
    HWND hWindow = NULL;

    // record starting time
    start_time = get_wall_time();    

    for (int i = 0; i < MAX_LOOP; ++i)
    {
        // API GetForegroundWindow() is exported user32.dll.
        // By using delay-load, user32.dll is not loaded into memory
        // until GetForegroundWindow() is being called.
        hWindow = GetForegroundWindow();
        if (!hWindow)
        {
            printf("GetActiveWindow() failed.\n");
            exit(1);
        }
        hWindow = NULL;
    }

    // record ending time
    end_time = get_wall_time();
    total_time = end_time - start_time;

    // print results
    printf("total time in nanoseconds is %llu\n", (long long unsigned int) total_time);
    return 0;
}