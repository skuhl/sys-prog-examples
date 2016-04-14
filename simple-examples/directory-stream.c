// Scott Kuhl
//
// This demonstrates how to use directory streams which allows you to
// get a list of files in a directory.
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <dirent.h>

int main(void)
{
	DIR* ds = opendir(".");
	if(ds == NULL)
	{
		perror("opendir");
		exit(EXIT_FAILURE);
	}

	/* See man page for readdir() for a description of the dirent
	 * struct */
	struct dirent* result;
	struct dirent currentEntry;
	while(1)
	{
		if(readdir_r(ds, &currentEntry, &result) != 0)
		{
			perror("readdir_r");
			exit(EXIT_FAILURE);
		}
		if(result == NULL)
			break; // exit loop

		printf("%s is at inode %ld\n", currentEntry.d_name, (long) currentEntry.d_ino);
	}

	closedir(ds);
}
