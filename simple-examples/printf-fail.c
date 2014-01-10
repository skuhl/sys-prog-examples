// Scott  Kuhl
//
// Even functions like printf() that you may think would always work can fail.
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	fclose(stdout);
	if(printf("Hello world\n") < 0)
		// write to stderr, since writing to stdout obviously won't work...
		fprintf(stderr, "printf failed.\n");
	return 0;
}

