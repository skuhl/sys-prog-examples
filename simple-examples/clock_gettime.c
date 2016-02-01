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

void print_timespec(struct timespec diff, const char *name)
{
	printf("%s.tv_sec=%ld  %s.tv_nsec=%ld\n", name, diff.tv_sec, name, diff.tv_nsec);
}


int main(void)
{
#ifdef __linux__
	struct timespec t1, t2;
	clock_gettime(CLOCK_MONOTONIC, &t1);
	sleep(5);
	clock_gettime(CLOCK_MONOTONIC, &t2);

	print_timespec(t1, "t1");
	print_timespec(t2, "t2");


	struct timespec diff;
	if(t2.tv_nsec < t1.tv_nsec)
	{
		/* If nanoseconds in t1 are larger than nanoseconds in t2, it
		   means that something like the following happened:
		   t1.tv_sec = 1000    t1.tv_nsec = 100000
		   t2.tv_sec = 1001    t2.tv_nsec = 10

		   In this case, less than a second has passed but subtracting
		   the tv_sec parts will indicate that 1 second has passed. To
		   fix this problem, we subtract 1 second from the elapsed
		   tv_sec and add one second to the elapsed tv_nsec. See
		   below:
		*/
		diff.tv_sec  = t2.tv_sec  - t1.tv_sec  - 1;
		diff.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
	}
	else
	{
		diff.tv_sec  = t2.tv_sec  - t1.tv_sec;
		diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
	}

	printf("Time elapsed   (float): %.15f seconds\n", diff.tv_sec + (double) diff.tv_nsec / 1000000000L);
	printf("Time elapsed (integer): %5ld seconds plus %12ld nanoseconds\n", diff.tv_sec, diff.tv_nsec);
	printf("                  Note: %5ld second   is  %12ld nanoseconds\n", 1L, 1000000000L);
#else
	printf("clock_gettime() works only on Linux\n");
#endif
	
	return 0;
}
