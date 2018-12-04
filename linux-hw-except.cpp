#include <signal.h>
#include <setjmp.h>
#include <stdio.h>
#include "helper.h"

sigjmp_buf mark;

void myhandler(int signo) {
    siglongjmp(mark, -1);
}

void exception_loop(void) {
    char *p = NULL;
    *p = 5;
}

int main(void) {
    NANOSECOND start_time;
    NANOSECOND end_time;
    NANOSECOND total_time;
    struct sigaction myhandle;

    myhandle.sa_handler = myhandler;
    sigemptyset(&myhandle.sa_mask);
    myhandle.sa_flags = SA_NODEFER;
    sigaction(SIGSEGV, &myhandle, NULL);

    start_time = get_wall_time();
    int i = 0;
    sigsetjmp(mark, 0);
    if (i++ < MAX_LOOP)
        exception_loop();
    end_time = get_wall_time();
    total_time = end_time - start_time;

    printf("total time in nanoseconds is %llu\n", (long long unsigned int) total_time);

    return 0;
}
