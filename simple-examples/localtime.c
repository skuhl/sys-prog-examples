// Scott Kuhl
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// variables set by ctime(). See "man tzset" for info
extern char *tzname[2];
extern long timezone;
extern int daylight;

int main(void)
{
	printf("static variables before calling localtime(): tzname=%s timezone=%ld daylight=%d\n", tzname[1], timezone, daylight);

	// use localtime_r() for reentrant version. localtime() will
	// return the same memory address each time. We are not supposed
	// to free() it. See ctime.c for another similar example.
	time_t t = time(NULL);
	struct tm *tstruct = localtime(&t);

	printf("static variables after calling localtime(): tzname=%s timezone=%ld daylight=%d\n", tzname[1], timezone, daylight);

	printf("Local time:\n");
	printf("seconds      %d\n", tstruct->tm_sec);
	printf("minutes      %d\n", tstruct->tm_min);
	printf("hours        %d\n", tstruct->tm_hour);
	printf("day in month %d\n", tstruct->tm_mday);
	printf("month        %d\n", tstruct->tm_mon);
	printf("year         %d\n", tstruct->tm_year);
	printf("day of week  %d\n", tstruct->tm_wday);
	printf("day of year  %d\n", tstruct->tm_yday);
	printf("is dst       %d\n", tstruct->tm_isdst);
	printf("%s\n", asctime(tstruct));
	// free(tstruct); // WRONG!
	time_t converted = mktime(tstruct);

	// These two values will match---converting a local time struct
	// back to a t_time should match the current time().
	printf("time_t: %ld %ld (diff=%ld)\n", converted, time(NULL), converted-time(NULL));

	
	t = time(NULL);
	tstruct = gmtime(&t);

	
	printf("\n");
	printf("UTC time:\n");
	printf("seconds      %d\n", tstruct->tm_sec);
	printf("minutes      %d\n", tstruct->tm_min);
	printf("hours        %d\n", tstruct->tm_hour);
	printf("day in month %d\n", tstruct->tm_mday);
	printf("month        %d\n", tstruct->tm_mon);
	printf("year         %d\n", tstruct->tm_year);
	printf("day of week  %d\n", tstruct->tm_wday);
	printf("day of year  %d\n", tstruct->tm_yday);
	printf("is dst       %d\n", tstruct->tm_isdst);
	printf("%s\n", asctime(tstruct));

	// convert a structure back to a time_t object. tstruct should be
	// in the local time zone. time_t is seconds since Epoch in UTC:
	converted = mktime(tstruct);
		
	// These two values will NOT match---we converted a UTC time
	// struct back to a time_t. However, during that conversion, we
	// assumed that the input was in local time (despite it actually
	// being UTC). As always, time_t is in UTC time.
	printf("time_t: %ld %ld (diff: %ld)\n", converted, time(NULL), converted-time(NULL));
	
	return 0;
}
