// Scott Kuhl
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#define READ_END 0
#define WRITE_END 1

int main(void)
{
	int fd[2];
	if(pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	if(write(fd[WRITE_END], "hello", 5) == -1)
	{
		perror("write");
		exit(EXIT_FAILURE);
	}
	close(fd[WRITE_END]); // TRY THIS: What happens if we don't close the write end?

	while(1)
	{
		char buf;
		ssize_t readRetVal = read(fd[READ_END], &buf, 1);
		if(readRetVal == 0)
		{
			printf("Read end of file from pipe\n");
			exit(EXIT_SUCCESS);
		}
		else if(readRetVal == -1)
		{
			perror("write");
			exit(EXIT_FAILURE);
		}
		else
		{
			printf("Read character %c\n", buf);
		}
	}
}
