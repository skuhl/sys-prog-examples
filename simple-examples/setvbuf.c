// Scott Kuhl
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	printf("'Hello world' will be printed after one second:\n");
	printf("Hello ");
	sleep(1);
	printf("World\n");
	


	printf("'Hello' will be printed, program sleeps for 1 second, and then world will be printed.\n");
	printf("Hello ");
	fflush(stdout);
	sleep(1);
	printf("World\n");

	// disable buffering:
	setvbuf(stdout, (char *) NULL, _IONBF, 0);
	printf("First example (stdout buffering turned off):\n");
	printf("Hello ");
	sleep(1);
	printf("World");

	return 0;
}
