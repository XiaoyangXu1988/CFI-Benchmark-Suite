#include "helper.h"

NANOSECOND start_time;
NANOSECOND end_time;
NANOSECOND total_time;

typedef void(*INC)(int&);

using namespace std;

int main()
{
	int loop_count = 50;
    void *lib_handle;
    double (*cosine)(double);
    char *error;
    double acc = 0;

	// record starting time
	start_time = get_wall_time();	

	for (int i = 0; i < loop_count; ++i)
	{
		// load an (un)trusted module libm.dll
        string nameOfLibToLoad("/lib/x86_64-linux-gnu/libm-2.27.so");
		lib_handle = dlopen(nameOfLibToLoad.c_str(), RTLD_LAZY);
        
		if (!lib_handle) {
            fputs (dlerror(), stderr);
            exit(1);
        }

		// get cos function pointer exported by libm.dll
        cosine = (double (*)(double)) dlsym(lib_handle, "cos");
        
		if ((error = dlerror()) != NULL)  {
            fputs(error, stderr);
            exit(1);
        }
		
        acc += (*cosine)(i);
        
		// unload lib.dll
		dlclose(lib_handle);
	}

	// record ending time
	end_time = get_wall_time();
	total_time = end_time - start_time;

	// print results
	printf("total time in nanoseconds is %llu\n", (long long unsigned int) total_time);
    printf("Sum of cos i for i in [0, 50) = %f\n", acc);
	return 0;
}
