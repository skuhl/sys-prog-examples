// Scott Kuhl
//
// Demonstrates how to convert a file descriptor into a file stream
// pointer and back. Although it is best to try avoid doing this
// because it adds complexity to your program, it can be useful!
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FILENAME "fileio-convert.temp"

int main(void)
{
	// "w+" means read+write+create file if it doesn't exist.
	// See "man 3 fopen" for more information.
	FILE *fs = fopen(FILENAME, "w+");
	if(fs == NULL) { perror("fopen"); exit(EXIT_FAILURE); };

	int fd = fileno(fs);
	write(fd, "hello\n", 6);

	// close only one of the two file descriptors. Closing both of
	// them will cause an error!
	if (fclose(fs) == -1) { perror("fclose"); };
	// if (close(fd) == -1) { perror("close"); };


	// Convert a file descriptor to a FILE*:
	fd = open(FILENAME, O_RDONLY);
	if(fd == -1) { perror("open"); exit(EXIT_FAILURE); };
	fs = fdopen(fd, "r");
	if(fs == NULL) { perror("fdopen"); exit(EXIT_FAILURE); };
	char buf[100];
	fgets(buf, 100, fs);
	printf("Read: %s", buf);

	// close only one of the two file descriptors. Closing both of
	// them will cause an error!
//	if (close(fd) == -1) { perror("close"); };
	if (fclose(fs) == -1) { perror("fclose"); };

	unlink(FILENAME);
	return EXIT_SUCCESS;
}
