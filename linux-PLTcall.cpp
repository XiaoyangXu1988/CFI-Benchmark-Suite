#include "helper.h"

NANOSECOND start_time;
NANOSECOND end_time;
NANOSECOND total_time;

int main()
{
    char *p;
    int page_size;
    int fd;
    
	// record starting time
	start_time = get_wall_time();	
    page_size = getpagesize();

	for (long long int i = 0; i < MAX_LOOP * LPLTTS; ++i)
	{
        fd = open ("/dev/zero", O_RDONLY);
        p = (char *) mmap (NULL, page_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
        close (fd);
        
        if (!p) {
            perror("Couldn’t malloc(1024)");
            exit(errno);
        }
        
        p[123] = 123;
        
        if (mprotect(p, page_size, PROT_NONE)) {
            perror("Couldn’t mprotect");
            exit(errno);
        }
        
        munmap(p, page_size);
	}

	// record ending time
	end_time = get_wall_time();
	total_time = end_time - start_time;

	// print results
	printf("total time in nanoseconds is %llu\n", (long long unsigned int) total_time);
	return 0;
}
