// Scott Kuhl
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	printf("Creating a temporary file...\n");
	// create a file w+b mode, probably in /tmp.  File will
	// automatically be deleted when closed or at exit() (similar to
	// how atexit() works).
	FILE *tmp = tmpfile(); 
	fprintf(tmp, "Hello world");
	fclose(tmp);

#if 0
	// THE CODE IN THIS PREPROCESSOR IF STATEMENT IS DANGEROUS OR PROBLEMATIC.

	// We don't demonstrate mktemp() in this example. It is dangerous too (see NOTES in "man 3 mktemp")
	
	for(int i=0; i<5; i++)
	{
		// generate a temp file name
		char *s = tmpnam(NULL); // returns a statically allocated area of memory---don't free() it!
		printf("temp file %d is %s\n", i, s);

		// Using tmpnam() is dangerous. It doesn't guarantee the
		// file is deleted when we exit. And, it is possible that some
		// other process could create that temporary file before we
		// create it (even if it didn't exist when tmpnam() was
		// called.
	}
#endif

	// mkstemp gives you a little more control over temp files. There
	// are several other variations too. See the man page.
	
	char tfile[] = "/tmp/my-temp-file-XXXXXX";
	int fd = mkstemp(tfile);
	printf("Created: %s\n", tfile);

	/* WRONG. Parameter must be a string that mkstemp() can
	 * modify---and string literals like this can't be modified! */
	// int fd = mkstemp("/tmp/my-tmp-file-XXXXXX"); 

	/* WRONG: Still a pointer to a string literal. */
    // char *tfile = "/tmp/my-temp-file-XXXXXX";
    // int fd = mkstemp(tfile);

	if(fd == -1)
	{
		perror("mkstemp");
		exit(1);
	}
	write(fd, "hello", 5);
	close(fd);
	// mkstemp() does NOT delete the files automatically on exit.
	unlink(tfile);

	return 0;
}
