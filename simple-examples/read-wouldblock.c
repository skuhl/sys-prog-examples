// Scott Kuhl
//
// File descriptors can be made non-blocking and then read() will not
// ever block. Instead, it will return an error value and set errno to
// a value that we can use to determine if read() would have normally
// blocked.
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
int main(void)
{
	printf("Blocking on read...press enter to unblock.\n");
	int c;
	read(STDIN_FILENO, &c, 1);

	printf("Now making stdin non-blocking\n");
	int flags;
	flags = fcntl(STDIN_FILENO, F_GETFL, 0);
	flags |= O_NONBLOCK;
	fcntl(STDIN_FILENO, F_SETFL, flags);
	
	// If the user typed something above (instead of just pressing
	// "enter" like we asked them to), it is possible that there are
	// still bytes to read and the read() below would succeed. If the
	// user only types enter, then the read() above would read the
	// newline character and the read() below wouldn't have any thing to
	// read.
	
	printf("Press enter again to exit the program...\n");
	while(1)
	{
		int ret = read(STDIN_FILENO, &c, 1);
		if(ret == -1)
		{
			if(errno == EAGAIN || errno == EWOULDBLOCK)
				printf("read() would have blocked\n");
			else
			{
				perror("read");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			printf("read succeeded\n");
			exit(EXIT_SUCCESS);
		}
		sleep(1);
	}
	exit(EXIT_SUCCESS);
}
