#include "helper.h"

NANOSECOND start_time;
NANOSECOND end_time;
NANOSECOND total_time;

typedef void(*INC)(int&);

int main()
{
    #ifdef _WIN32
    HINSTANCE libHandle = NULL;
    BOOL retFree = FALSE;
    #elif __linux__
    void *libHandle;
    char *error;
    #endif
    INC pInc = NULL;
    int count = 0;

    // record starting time
    start_time = get_wall_time();    

    for (long long int i = 0; i < MAX_LOOP * DYNLTS; ++i)
    {
        // load an untrusted module libinc.dll/.so
        #ifdef _WIN32
        libHandle = LoadLibrary(L"lib.dll");
        #elif __linux__
        libHandle = dlopen("./libinc.so", RTLD_LAZY);
        #endif
        if (!libHandle)
        {
            printf("Loading library failed.\n");
            exit(1);
        }

        // get a function pointer exported by libinc.dll/.so
        #ifdef _WIN32
        pInc = (INC)GetProcAddress(libHandle, "increment");
        #elif __linux__
        pInc = (INC) dlsym(libHandle, "increment");
        #endif
        if (!pInc)
        {
            printf("Finding symbol failed.\n");
            exit(1);
        }

        pInc(count);

        // unload libinc.dll/.so
        #ifdef _WIN32
        retFree = FreeLibrary(libHandle);
        if (!retFree)
        {
            printf("FreeLibrary() failed.\n");
            exit(1);
        }
        #elif __linux__
        dlclose(libHandle);
        #endif
    }

    // record ending time
    end_time = get_wall_time();
    total_time = end_time - start_time;

    // print results
    printf("total time in nanoseconds is %llu\n", (long long unsigned int) total_time);
    printf("count is %d\n", count);
    return 0;
}
