#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <limits.h>

int main()
{
	struct timeval time;
	struct timeval after;
	struct timeval before;

	// gettimeofday(&time, NULL);
	// printf("get time = %ld\n", time.tv_usec);
	// usleep(100);
	// gettimeofday(&time, NULL);
	// printf("get time + 100 usec = %ld\n", time.tv_usec);
	// usleep(100);
	// gettimeofday(&time, NULL);
	// printf("get time + 100 usec = %ld\n", time.tv_usec);
	// usleep(100);
	// gettimeofday(&time, NULL);
	// printf("get time + 100 usec = %ld\n", time.tv_usec);
	gettimeofday(&before, NULL);
	printf("before = %ld\n", before.tv_usec);  
	sleep(1);
	gettimeofday(&after, NULL);
	printf("after = %ld\n", after.tv_usec);
	time.tv_usec = after.tv_usec - before.tv_usec;
	printf("difference = %ld\n", time.tv_usec);

	return 0;
}