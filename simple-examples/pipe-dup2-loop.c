// Scott Kuhl
//
// This demonstrates how you can make writing to stdout result in
// bytes that we can read in from stdin.
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define READ_END 0
#define WRITE_END 1

int main(void)
{
	int fd[2];
	pipe(fd);

	// when we write to stdout, actually write to the WRITE_END.
	if(dup2(fd[WRITE_END], STDOUT_FILENO)==-1)
		perror("dup2");
	// when we read from stdin, actually read from READ_END.
	if(dup2(fd[READ_END],  STDIN_FILENO)==-1)
		perror("dup2");

	// write something to stdout.
	printf("Hi\n");
	fflush(stdout);

	// read a byte from stdin and then write it to stdout.
	char byte[1];
	while(read(STDIN_FILENO, byte, 1))
	{
		write(STDOUT_FILENO, byte, 1);

		// print to stderr so we can see what is going on:
		fwrite(byte, 1, 1, stderr);
	}

	close(fd[READ_END]);
	close(fd[WRITE_END]);
}
