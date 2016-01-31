// Scott Kuhl

/* Demonstrates what happens when you use fopen() to open the same
   file repeatedly. This example serves no purpose other than to
   demonstrate that processes have limits imposed by the OS that they
   must stay within. */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	for(int i=0; i<100000; i++)
	{
		FILE *f = fopen("fileio-fopen-repeat.c", "r");
		if(f == NULL)
		{
			printf("fopen() failed when i=%d\n", i);
			perror("fopen");
			exit(EXIT_FAILURE);
		}

	}

	/* TRY THIS: Try using the command-line program 'limit' (or
	   'ulimit', depending on your system) to show you how many file
	   descriptors a process is allowed to open. You may have to pass
	   a parameter such as '-a' to show all of the limits. */

	/* TRY THIS: Use "lsof | grep $USER | grep REG" to show a listing
	   of regular files that are open on your computer---and a note
	   about which processes are using which files.

	/* Here, we don't call fclose(). The OS will release the file
	   descriptors. However, it is good practice to call fclose() on
	   files when you are done with them. */
	
	return EXIT_SUCCESS;
}
