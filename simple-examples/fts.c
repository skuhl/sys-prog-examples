// Scott Kuhl

// fts() traverses a directory hierarchy. It works on Linux, Mac OS X,
// and the BSDs.
//
// fts() is the recommended way to traverse directories on Mac OS X
// because fts() is considered "legacy".
//
// A POSIX standard function which provides similar functionality is
// demonstrated in ftw.c

#define _BSD_SOURCE // required to make this program work on Linux
#include <stdio.h>
#include <stdlib.h>

#include <sys/errno.h> // lets us directly access errno

// includes recommended by "man fts":
#include <sys/types.h>
#include <sys/stat.h>
#include <fts.h>

int main(void)
{
	/* An array of paths to traverse. Each path must be null
	 * terminated and the list must end with a NULL pointer. */
	char *paths[] = { ".", NULL };
	
	/* 2nd parameter: An options parameter. Must include either
	   FTS_PHYSICAL or FTS_LOGICAL---they change how symbolic links
	   are handled.

	   Last parameter is a comparator which you can optionally provide
	   to change the traversal of the filesystem hierarchy.
	*/
	FTS *ftsp = fts_open(paths, FTS_PHYSICAL, NULL);
	if(ftsp == NULL)
	{
		perror("fts_open");
		exit(EXIT_FAILURE);
	}

	while(1) // call fts_read() enough times to get each file
	{
		FTSENT *ent = fts_read(ftsp); // get next entry (could be file or directory).
		if(ent == NULL)
		{
			if(errno == 0)
				break; // No more items, bail out of while loop
			else
			{
				// fts_read() had an error.
				perror("fts_read");
				exit(EXIT_FAILURE);
			}
		}
			
		// Given a "entry", determine if it is a file or directory
		if(ent->fts_info & FTS_D)   // We are entering into a directory
			printf("Enter dir: ");
		else if(ent->fts_info & FTS_DP) // We are exiting a directory
			printf("Exit dir:  ");
		else if(ent->fts_info & FTS_F) // The entry is a file.
			printf("File:      ");
		else // entry is something else
			printf("Other:     ");

		// print path to file after the label we printed above.
		printf("%s\n", ent->fts_path);
	}

	// close fts and check for error closing.
	if(fts_close(ftsp) == -1)
		perror("fts_close");
	return 0;
}
