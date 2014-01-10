// Scott Kuhl
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>


#define READ_END 0
#define WRITE_END 1

int main(void)
{
	int fd[2];
	pipe(fd);

	// If we filled the pipe normally, write() would hang. Here we
	// make the file descriptor non-blocking so it will return and set
	// errno indicating that the call would have blocked.
	int flags = fcntl(fd[WRITE_END], F_GETFL, 0);
	flags |= O_NONBLOCK;
	fcntl(fd[WRITE_END], F_SETFL, flags);

	int i=0;
	char x = 'x';


	while(write(fd[WRITE_END], &x, 1) == 1)
		i++;

	perror("write() perror message");
	if(errno == EAGAIN || errno == EWOULDBLOCK)
		printf("errno indicates that we would have blocked\n");

	printf("wrote %d bytes into pipe\n", i);
	
	return 0;

}
