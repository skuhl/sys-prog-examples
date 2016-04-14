// Scott Kuhl

// fts() traverses a directory hierarchy. It works on Linux, Mac OS X,
// and the BSDs. A POSIX standard function which provides similar
// functionality is demonstrated in ftw.c

#include <stdio.h>
#include <stdlib.h>

#include <sys/errno.h>

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

	while(1)
	{
		FTSENT *ent = fts_read(ftsp);
		if(ent == NULL)
		{
			if(errno == 0)
				break; // No more items, bail out of while loop
			else
			{
				perror("fts_read");
				exit(EXIT_FAILURE);
			}
		}
			
			
		if(ent->fts_info & FTS_D)
			printf("Enter dir: ");
		else if(ent->fts_info & FTS_DP)
			printf("Exit dir:  ");
		else if(ent->fts_info & FTS_F)
			printf("File:      ");
		else
			printf("Other:     ");

		// print path to file
		printf("%s\n", ent->fts_path);
	}

	// close fts and check for error closing.
	if(fts_close(ftsp) == -1)
		perror("fts_close");
	return 0;
}
