// Scott Kuhl
//
// This example uses clock_gettime() to demonstrate a robust way to
// measure elapsed time which works even if the system administrator
// changes the system clock.

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(void)
{
#ifdef __linux__
	struct timespec t1, t2;
	clock_gettime(CLOCK_MONOTONIC, &t1);
	sleep(5);
	clock_gettime(CLOCK_MONOTONIC, &t2);

	struct timespec diff;
	if(t2.tv_nsec-t1.tv_nsec < 0)
	{
		diff.tv_sec  = t2.tv_sec  - t1.tv_sec  - 1;
		diff.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
	}
	else
	{
		diff.tv_sec  = t2.tv_sec  - t1.tv_sec;
		diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
	}

	double secondsElapsed = diff.tv_sec + diff.tv_nsec / 1000000000.0;
	printf("Time elapsed (in seconds): %f\n", secondsElapsed);
#else
	printf("clock_gettime() works only on Linux\n");
#endif
	
	return 0;
}
