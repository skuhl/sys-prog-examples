// Scott Kuhl
//
// Demonstrates using open(), close(), lseek()
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define FILENAME "fileio-open.temp"

int main(void)
{
	// Create a file and open it for read/write. Set permissions so
	// only owner can read/write the file.  See "man 2 open" for more
	// information.
	//
	// Third parameter to open() is required if O_CREAT is specified
	// in the second paramter. The third parameter is the permission
	// of the file that (might) get created. The 3rd parameter is in
	// octal. In C, numbers that start with 0 are in
	// octal. Alternatively, you can use predefined variables such as
	// S_IRUSR (see the "man 2 open" for a complete least of available
	// options.
	int fd = open(FILENAME, O_CREAT|O_RDWR, 0600);
	if(fd == -1) { perror("open"); exit(EXIT_FAILURE); };

	// write(), lseek(), & close() can return -1 on error too--but we
	// aren't checking those things in this program.
	write(fd, "Hello      \n", strlen("Hello      \n"));
	lseek(fd, -6, SEEK_CUR); // seek backward from our current position.
	write(fd, "world", strlen("world"));
	close(fd);

	fd = open(FILENAME, O_RDONLY);
	if(fd == -1) { perror("open"); exit(EXIT_FAILURE); };
	int done = 0;
	while(!done)
	{
		char c;
		int ret = read(fd, &c, 1);
		if(ret == -1)
			perror("read");
		else if(ret == 0)
			done = 1;
		else
			printf("%c", c);
	}
	close(fd);

	unlink(FILENAME);
	
	return EXIT_SUCCESS;
}
