// Scott Kuhl

/* Demonstrates POSIX functions nanosleep() and usleep(). This example
   also uses POSIX function gettimeofday() to try to measure how long
   we slept for.
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   // usleep()
#include <time.h>     // nanosleep()
#include <sys/time.h> // gettimeofday()


/* gettimeofday() with error checking. Has approximately microsecond
 * accuracy. For a more accurate timer, see rdtsc.c or
 * clock_gettime.c */
struct timeval my_gettimeofday(void)
{
	struct timeval ret;
	if(gettimeofday(&ret, NULL) == -1)
	{
		perror("gettimeofday");
		exit(EXIT_FAILURE);
	}
	return ret;
}


void print_elapsed(struct timeval start, struct timeval end)
{
	long elapsed_microsec = ((end.tv_sec-start.tv_sec) * 1000000L) + (end.tv_usec-start.tv_usec);
	printf("Slept for approximately %.20f seconds or %ld microseconds\n",
	       (double) elapsed_microsec / 1000000L, elapsed_microsec);
}

/* Sleeps for 'sec' seconds + 'nanosec' nanoseconds. 'nanosec' must be no larger than 1 billion.

   There are a billion (1,000,000,000) nanoseconds in a second. */
void sleep_nanoseconds(long sec, long nanosec)
{
	struct timespec ts;
	ts.tv_sec  = sec;
	ts.tv_nsec = nanosec;
	
	if(nanosleep(&ts, NULL) == -1)
	{
		perror("nanosleep");
		exit(EXIT_FAILURE);
	}
}


int main(void)
{
	struct timeval start, end;

	printf("Sleeping for 0 seconds\n");
	start = my_gettimeofday();
	// do nothing!
	end = my_gettimeofday();
	print_elapsed(start, end);
	printf("\n");

	/* Note: This example, doesn't make much sense. 1 nanosecond is 1
	 * billionth of a second. If you have a 3Ghz processor, 1
	 * nanosecond is three clock cycles. Therefore, we can't expect
	 * that this is actually going to sleep just 1 nanosecond. We are
	 * really just measuring the overhead of the call. In addition,
	 * gettimeofday() really only has microsecond accuracy. */
	printf("nanosleep: Sleeping for 1 nanosecond or %.10f seconds\n", (double)1/1000000000);
	start = my_gettimeofday();
	sleep_nanoseconds(0, 1);
	end = my_gettimeofday();
	print_elapsed(start, end);
	printf("\n");


	printf("nanosleep: Sleeping for 100000 nanoseconds, 100 microseconds, or %.10f seconds\n", (double)100000/1000000000);
	start = my_gettimeofday();
	sleep_nanoseconds(0, 100000);
	end = my_gettimeofday();
	print_elapsed(start, end);
	printf("\n");


	
	printf("usleep: Sleeping for 1 microsecond or %.10f seconds\n", (double)1/1000000);
	start = my_gettimeofday();
	if(usleep(1) != 0)
	{
		perror("usleep");
		exit(EXIT_FAILURE);
	}
	end = my_gettimeofday();
	print_elapsed(start, end);
	printf("\n");


	printf("usleep: Sleeping for 100 microseconds or %.10f seconds\n", (double)100/1000000);
	start = my_gettimeofday();
	if(usleep(100) != 0)
	{
		perror("usleep");
		exit(EXIT_FAILURE);
	}
	end = my_gettimeofday();
	print_elapsed(start, end);
}
