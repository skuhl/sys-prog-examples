// Scott Kuhl
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

void printTimeReentrant(time_t t)
{
	char humanTime[128];
	ctime_r(&t, humanTime); // stores result in humanTime buffer.
	// NOTE: Should check return value of ctime_r()!
	printf("0x%lx or %ld is %s\n\n", t, t, humanTime);
}

void printTime(time_t t)
{
	char *humanTime = ctime(&t);
	// NOTE: Should check return value of ctime()!
	printf("0x%lx or %ld is %s (string is at address 0x%lx)\n\n", (unsigned long)t, (unsigned long)t, humanTime, (unsigned long)humanTime);

	// Don't free what ctime() returns. The documentation explains
	// that it returns a static location in memory. If you call
	// printTime() multiple times you will see that it always stores
	// the result in the same place!
	//
	//free(humanTime); // WRONG!
}

// variables set by ctime(). See "man tzset" for info
extern char *tzname[2];
extern long timezone;
extern int daylight;

int main(void)
{
	// Gets seconds since UTC Epoch.
	time_t t = time(NULL);
	printf("static variables before calling ctime(): tzname=%s timezone=%ld daylight=%d\n", tzname[1], timezone, daylight);
	printTime(t);
	printf("static variables after calling ctime(): tzname=%s timezone=%ld daylight=%d\n", tzname[1], timezone, daylight);

	// Epoch isn't necessarily 00:00 on Jan 1 1970 in every time
	// zone. The epoch happened in UTC timezone---and this will print
	// when the epoch was in our timezone:
	printTime((time_t) 0);

	// Time is a signed value. This is one second before the epoch.
	printTime((time_t) -1);

	// On my machine, time_t is the same size as a long. Print some
	// big and some small time values.
	printf("sizeof(time_t): %zd\n", sizeof(time_t));
	printf("sizeof(long): %zd\n", sizeof(long));
	printTime((time_t) (LONG_MAX/350));
	printTime((time_t) (LONG_MIN/350));
	// reentrant versions will only print up to 26 characters---here
	// the date gets truncated!
	printTimeReentrant((time_t) (LONG_MAX/350));
	printTimeReentrant((time_t) (LONG_MIN/350));

//	printf("%ld\n", (time_t) LONG_MAX);
	
	// ctime() can return errors:
	printTime((time_t) (LONG_MAX));

	return 0;
}
