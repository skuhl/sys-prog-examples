// Scott Kuhl
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	if(raise(SIGSEGV) == 0) // cause crash, try other signals here.
		printf("Successfully sent the signal\n");
	else
		printf("Failed to send signal\n");
	
	return EXIT_SUCCESS;
}
