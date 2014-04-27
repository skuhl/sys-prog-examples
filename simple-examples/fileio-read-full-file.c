// Scott Kuhl
//
// This program demonstrates how to read a file into memory. It
// provides a function which attempt to check for many of the errors
// that might occur.
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

char *readfile(char *filename, size_t *filesize)
{
	*filesize = 0; // If we return before reading file, set filesize to 0.

	// Check if inputs are OK
	if(filename == NULL || filesize == NULL)
		return NULL;

	// Try to open the file
	int fd = open(filename, O_RDONLY);
	if(fd == -1)
	{
		perror("open");
		return NULL;
	}

	// Get information about the file. If we happened to open a
	// directory, the result is undefined. We can't check before we
	// call fopen() because there is a race condition: Someone could
	// replace a file with a directory between our call to stat and
	// open().
	struct stat result;
	if(fstat(fd, &result) == -1)
	{
		perror("stat");
		close(fd);
		return NULL;
	}

	// If file is not a regular file, don't try to read it.
	if(!S_ISREG(result.st_mode))
	{
		fprintf(stderr, "Not a file: %s\n", filename);
		close(fd);
		return NULL;
	}

	// Get the size of the file
	off_t size = result.st_size;
	*filesize = (size_t) size; // cast result to what caller is expecting.

	// Are we reading a file with no data?
	if(size == 0)
	{
		close(fd);
		return NULL;
	}

	// Try to allocate space to store file.
	char *fileContents = (char*) malloc(sizeof(char) * size);
	if(fileContents == NULL)
	{
		fprintf(stderr, "malloc() failed.\n");
		close(fd);
		return NULL;
	}

	// Try to read the file.
	if(read(fd, fileContents, size) < (ssize_t) size)
	{
		perror("read");
		fprintf(stderr, "We read less from the file than we expected due to the problem above.\n");

		free(fileContents);
		close(fd);
		return NULL;
	}

	// See if there is more to read than we expected.
	if(read(fd, fileContents, 1) == 1)
	{
		fprintf(stderr, "File increased in size unexpectedly.\n");
		free(fileContents);
		close(fd);
		return NULL;
	}

	// NOTE: We could deal with changing file sizes by using realloc()
	// to change the size of space that we had allocated.
	
	// Try to close the file. If we fail to close the file, print an
	// error message, but we can still return the bytes that we read.
	if(close(fd) != 0)
		perror("close");

	// Caller should free the returned variable.
	return fileContents;
}


int main(void)
{
	size_t size;
	printf("=== Makefile ===\n");
	char *bytes = readfile("Makefile", &size);
	if(bytes)
	{
		fwrite(bytes, 1, size, stdout);
		free(bytes);
	}

	printf("\n\n=== readfile.c ===\n");
	bytes = readfile("readfile.c", &size);
	if(bytes)
	{
		fwrite(bytes, 1, size, stdout);
		free(bytes);
	}


	printf("\n\n=== Try reading a directory: /tmp ===\n");
	bytes = readfile("/tmp", &size);
	if(bytes)
	{
		fwrite(bytes, 1, size, stdout);
		free(bytes);
	}

	printf("\n\n=== Try reading something that doesn't exist ===\n");
	bytes = readfile("/does/not/exist", &size);
	if(bytes)
	{
		fwrite(bytes, 1, size, stdout);
		free(bytes);
	}

	
}
