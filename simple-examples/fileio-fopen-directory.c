// Scott Kuhl
//
// You shouldn't use fopen() to open a directory. This example
// demonstrates what happens if you try to do this. For more
// information, see:
// http://stackoverflow.com/questions/18192998/plain-c-opening-a-directory-with-fopen/18193383#18193383
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define DIRNAME "fileio-fopen-directory.temp"

void cleanup()
{
	rmdir(DIRNAME);
}

int isdir(char *path)
{
	struct stat st;
	if(stat(path, &st) != 0)
	{
		perror("stat");
		exit(EXIT_FAILURE);
	}
	return S_ISDIR(st.st_mode);
}

int main(void)
{
	mkdir(DIRNAME, 0700);

	// Demonstrate how to test if a path is a directory:
	if(isdir(DIRNAME))
		printf("%s is a directory\n", DIRNAME);
	else
		printf("%s is NOT a directory\n", DIRNAME);

	// Calling fopen() on a directory is undefined. You will see that
	// fopen doesn't have to return NULL in this case!
	FILE *fs = fopen(DIRNAME, "r");
	if(fs == NULL)
	{
		perror("fopen");
		cleanup();
		exit(EXIT_FAILURE);
	}

	printf("We fopen()'d a directory?!\n");

	// What if we try to read the directory?
	char buf[256];
	ssize_t bytesRead = fread(buf, 1, 256, fs);
	printf("We fread() %zu bytes from the directory.\n", bytesRead);

	// If fread() returns zero, how do we know if an error occurred?
	// Maybe reading a directory is like reading an empty file? "man 3
	// fread" clarifies that returning 0 means either we hit the end
	// of a file or an error occurred.

	if(bytesRead == 0)
	{
		if(feof(fs))
			printf("We reached the end of a file.");
		else if(ferror(fs))
			printf("An error occurred!\n");
	}

	fclose(fs);

	cleanup();
	return EXIT_SUCCESS;
}
