// Scott Kuhl

/* Demonstrates using fopen() to write to a file after it has been deleted. */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define FILENAME "fileio-fopen-delete.temp"

int main(void)
{
	printf("This is running as PID %d\n", getpid());
	FILE *f = fopen(FILENAME, "w");
	fprintf(f, "Hello ");
	fflush(f);

	// Delete the file!
	remove(FILENAME);

	// Write more to the file (now deleted!)
	fprintf(f, "World.");
	fflush(f);

	/* TRY THIS: Type
	   ls -l /proc/<PID>/fd
	   to see a list of files that this process has open.

	   You will see multiple files, each named a number and linked to
	   some other file. You can "cat" those files and see the contents
	   of them. One of them should be labeled as "(deleted)" or
	   otherwise named to something else. In other words, the deleted
	   file will stay there until it is closed (even though it was
	   actually deleted earlier).
	*/

	// Leave some time for the person to try the recommendation above.
	sleep(120);
	
	fclose(f);
	   
	return EXIT_SUCCESS;
}
