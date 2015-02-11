// Scott Kuhl
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	time_t t1 = time(NULL);
	printf("Wait a few seconds a press enter.");
	char str[10];
	fgets(str, 10, stdin);
	time_t t2 = time(NULL);

	printf("Time elapsed (in seconds):\n");
	double elapsed = difftime(t2, t1);
	printf("%lf\n", elapsed);

	// a similar way to calculate time elapsed...but size of time_t
	// depends on system.
	time_t elapsedAlternate= t2-t1;
	printf("%ld\n", elapsedAlternate);

	// Measuring elapsed time in this way can be somewhat
	// misleading. For example, a system administrator might change
	// the time after t1 is recorded but before t2 is recorded.
	//
	// To more robustly measure the amount of time that has elapsed,
	// look at clock_gettime.c
	
	return 0;
}
