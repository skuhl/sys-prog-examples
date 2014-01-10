// Scott Kuhl
// See "man 3 clock"
#include <time.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
	printf("CLOCKS_PER_SEC=%ld\n", CLOCKS_PER_SEC);
	sleep(5); // doesn't actually use CPU time
	clock_t c = clock();
	printf("CPU time used so far: %ld\n", c);
	int i=1;
	while(i < 1000000000) // use some CPU time.
		i=i+1;
	c = clock();
	printf("CPU time used so far: %ld\n", c);
	return 0;
}
