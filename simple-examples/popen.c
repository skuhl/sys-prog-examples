// Scott Kuhl
//
// popen() allows you to run a command and capture the output of it.
#define _POSIX_C_SOURCE 2
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char buf[1024];
	// Compare the output of this program to running "ps aux" on the
	// command line.
	FILE *in = popen("ps aux", "r");
	if(in == NULL)
	{
		perror("popen:");
		exit(EXIT_FAILURE);
	}

	// Write the output of the command to the console.
	while(fgets(buf, sizeof(buf), in) != NULL)
		printf("%s", buf);
	pclose(in);

	return EXIT_SUCCESS;
}
