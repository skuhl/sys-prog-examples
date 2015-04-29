// Scott Kuhl

/* gettimeofday() is a very useful way to determine the current time
 * and to measure elapsed time with high resolution. */
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h> // gettimeofday()
#include <limits.h>   // LONG_MAX
#include <time.h>     // strftime()

int main(void)
{
	struct timeval tv;
	if(gettimeofday(&tv, NULL) < 0)
	{
		perror("gettimeofday");
		exit(EXIT_FAILURE);
	}

	printf("Current time is %ld seconds + %ld microseconds\n", tv.tv_sec, tv.tv_usec);
	
	/* Current time in milliseconds is:
	   
	   Time in seconds * 1,000 (milliseconds/second)
	   +
	   Microseconds since last second * 1,000 (milliseconds/microsecond)

	   (Note: tv.tv_usec / 1000L does not results in truncation, not
	   rounding.)
	*/
	long milliseconds = (tv.tv_sec * 1000L) + tv.tv_usec / 1000L;

	
	/* Current time in microseconds is:
	   
	   Time in seconds * 1,000,000 (microseconds/second)
	   +
	   Microseconds since last second
	*/
	long microseconds = (tv.tv_sec * 1000000L) + tv.tv_usec;

	printf("combined milliseconds = %ld\n", milliseconds);
	printf("combined microseconds = %ld\n", microseconds);
	printf("maximum size of long  = %ld\n", LONG_MAX);
	printf("There are 1,000,000 microseconds in a second.\n");
	printf("There are     1,000 milliseconds in a second.\n");
	
	int days = tv.tv_sec / (60*60*24);
	printf("Days since epoch: %d\n", days);
	printf("Years since epoch: %d\n", days/365); // ignoring leap years


	/* Converting a timeval struct into a human readable value. */
	// http://stackoverflow.com/questions/2408976/struct-timeval-to-printable-format
	time_t nowtime = tv.tv_sec;
	struct tm *nowtm = localtime(&nowtime); 
    // nowtm is statically allocated, don't free, might be overwritten
    // with subsequent calls to localtime(). Use localtime_r() if you
    // want different behavior.
	
	char buf1[1024]; // construct a string without microseconds
	strftime(buf1, 1024, "%Y-%m-%d %H:%M:%S", nowtm);
	
	char buf2[1024]; // append microseconds to end of string
	snprintf(buf2, 1024, "%s.%06ld", buf1, tv.tv_usec);

	printf("%s\n", buf2);
}
