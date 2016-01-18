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

/** Reads an entire file into a buffer. Uses POSIX functions open(),
 * fstat(), read(), close(), etc.
 *
 * @param filename A name of the file to read. If the filename is
 * actually a directory, this function will fail.
 *
 * @param filesize The size of the file that we read.
 *
 * @return Returns the buffer which should be free()'d by the
 * caller. If an error occurs or if the file is empty, NULL is
 * returned.
 */
char *readfile_fstat(const char *filename, size_t *filesize)
{
	/* Set the filesize variable to 0, make sure caller didn't have
	 * filesize set to NULL. This ensures that filesize will be set to
	 * 0 in the event that we return NULL because of an error. */
	if(filesize == NULL)
		return NULL;
	*filesize = 0;

	/* If the filename is a null pointer instead of a string, return
	 * NULL */
	if(filename == NULL)
		return NULL;

	// Try to open the file to read from, check if we fail
	int fd = open(filename, O_RDONLY);
	if(fd == -1)
	{
		perror("open");
		return NULL;
	}

	/* Get file size (and other information) about the file that we
	   have already opened using fstat().

	   An alternate strategy would be to use stat() prior to opening
	   the file to figure out how large it is. Then open() the file
	   and read it. However, this could create a race condition: We
	   might get the file size, then the file might change, then we
	   might open() it.
	*/
	struct stat result;
	if(fstat(fd, &result) == -1)
	{
		perror("stat");
		close(fd);
		return NULL;
	}

	/* Make sure that the file that we opened is a regular file. If it
	   isn't, return an error. This catches the case where a caller
	   might try to read a directory. */
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

/** Reads an entire file into a buffer. Uses standard C functions
 * fopen(), fseek(), fread(), fclose(), etc.
 *
 * @param filename A name of the file to read. This variable will not
 * be changed by this function. This function does not verify that the
 * file is actually a file.
 *
 * @param filesize The size of the file that we read.
 *
 * @return Returns the buffer which should be free()'d by the
 * caller. If an error occurs or if the file is empty, NULL is
 * returned.
 */
char *readfile_stdc(const char *filename, size_t *filesize)
{
	// If filesize is a NULL pointer, return an error.
	if(filesize == NULL)
		return NULL;
	*filesize = 0;

	// If filename is NULL, return an error.
	if(filename == NULL)
		return NULL;

	// Try to open the file for reading, check for error.
	FILE *f = fopen(filename, "r");
	if(f == NULL)
	{
		perror("fopen");
		return NULL;
	}

	/* Now, use fseek() seek to the end of the file so we can figure
	   out the size of the file. Note that in standard C, this is not
	   guaranteed to work if we had fopen()'d the file in binary
	   mode. For more information, see:
	   https://www.securecoding.cert.org/confluence/display/c/FIO19-C.+Do+not+use+fseek()+and+ftell()+to+compute+the+size+of+a+regular+file
	*/

	// Seek to end of file, check for error.
	if(fseek(f, 0L, SEEK_END) != 0)
	{
		perror("fseek");
		fclose(f);
		return NULL;
	}
	// Get our current position in the file (i.e., at the end), check
	// for error
	long size = ftell(f);
	if(size == -1)
	{
		perror("ftell");
		fclose(f);
		return NULL;
	}
	// Seek back to the beginning of the file, check for error.
	if(fseek(f, 0L, SEEK_SET) != 0)
	{
		perror("fseek");
		fclose(f);
		return NULL;
	}
	
	// Store the size of the file in the pointer passed into this
	// function.
	*filesize = (size_t) size;

	// Try to allocate space to store file.
	char *fileContents = (char*) malloc(sizeof(char) * size);
	if(fileContents == NULL)
	{
		fprintf(stderr, "malloc() failed.\n");
		fclose(f);
		return NULL;
	}

	// Try to all bytes in the file. If we read less than we should,
	// return an error.
	if(fread(fileContents, 1, *filesize, f) < *filesize)
	{
		perror("fread");
		fprintf(stderr, "We read less from the file than we expected due to the problem above.\n");
		free(fileContents);
		fclose(f);
		return NULL;
	}

	// See if there is more to read than we expected.
	char oneMoreByte;
	if(fread(&oneMoreByte, 1, 1, f) == 1)
	{
		fprintf(stderr, "File increased in size unexpectedly.\n");
		free(fileContents);
		fclose(f);
		return NULL;
	}

	return fileContents;
}



char* readfile(const char *filename, size_t *filesize)
{
	// CHANGE ME to switch between the two different methods of
	// reading the file.
	
	//return readfile_fstat(filename, filesize);
	return readfile_stdc(filename, filesize);
}

int main(void)
{
	size_t size;
	printf("=== Makefile ===\n");
	char *bytes = readfile("Makefile", &size);
	if(bytes)
	{
		// printf("%s", bytes) would print bytes until a null
		// byte---and would require that the bytes array be null
		// terminated. We use write() which will write all bytes out
		// to the terminal no matter what they are.
		fwrite(bytes, 1, size, stdout);
		free(bytes);
	}

	printf("\n\n=== readfile.c ===\n");
	bytes = readfile("fileio-read-full-file.c", &size);
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
