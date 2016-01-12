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

	// Try this: Can you use quotes to make one of the arguments be an
	// empty string?

	
#if 0
	// Section 5.1.2.2.1 in C99 and C11 specify that argv[argc] must
	// contain NULL. In addition argv[0] through argv[argc-1] will
	// contain pointers to strings. Therefore, we could iterate on
	// argv until we reach NULL instead of using a for loop. For
	// example:

	int i=0; 
	while(argv[i] != NULL)
	{
		printf("argv[%d]=%s\n", i, argv[i]);
		i++;
	}
#endif

	return EXIT_SUCCESS;
}
