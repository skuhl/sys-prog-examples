// Scott Kuhl

/* This program demonstrates how to process user-supplied arguments to
 * your program. Try running this program as "./argv-argc hello world"
 * to see how it behaves.*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>


int main(int argc, char *argv[])
{
	// argc or "argument count" is the number of arguments passed used
	// when the program was run.

	// argv[] is an array of the arguments the passed when the program
	// was run.

	printf("Number of arguments passed to this program: %d (including the program executable itself!)\n", argc);
	for(int i=0; i<argc; i++)
		printf("argv[%d]=%s\n", i, argv[i]);
	return EXIT_SUCCESS;
}
