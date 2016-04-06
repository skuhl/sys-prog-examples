// Scott Kuhl
//
// This program does not check the return code of close(), dup2(),
// execlp(), fork(), and waitpid(). A good program would add those
// additional checks!
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define READ_END 0
#define WRITE_END 1

int main (void)
{
	int fd[2];
	pipe(fd);  // pipe() could return an error. I'm not checking it.

	int child1 = fork();
	if(child1 == 0) /* we are child 1 */
	{
		// we will be writing to the pipe, no need to read:
		close(fd[READ_END]);

		// When we write to stdout for this process, actually write to
		// the write end of the pipe. I.e., make the stdout file
		// descriptor be an "alias" for the write end of the pipe.
		//
		// To do this, dup2() will actually close stdout and then
		// create a new file descriptor with the same number as
		// stdout---and ensure that it behaves exactly the same as the
		// write end of the pipe.
		dup2(fd[WRITE_END], STDOUT_FILENO); // I'm not checking return value for error!
		execlp("ls", "ls", "-al", NULL);
		// execlp() does not return (except when an error occurred).
		
		printf("execlp() failed.\n");
		exit(EXIT_FAILURE); // exit child process if exec fails.
	}

	/* Only parent gets here. */
	pid_t child2 = fork();
	if(child2 == 0) /* we are child 2 */
	{
		// we will be reading from the pipe, no need to write:
		close(fd[WRITE_END]);
		// whenever we read from stdin, actually read from the pipe.
		dup2(fd[READ_END], STDIN_FILENO);
		// change every 's' into an 'X'
		execlp("tr", "tr","s", "X",NULL);
		// execlp() does not return (except when an error occurred)

		printf("execlp() failed.\n");
		exit(EXIT_FAILURE); // exit child process if exec fails.
	}
	/* Only parent gets here. If parent doesn't close the WRITE_END of
	 * the pipe, then child2 might not exit because the parent could
	 * still write data into the pipe that child2 is reading from. */
	close(fd[READ_END]);
	close(fd[WRITE_END]);

	/* We could call wait() twice here instead of using waitpid() on
	 * child2.
	 *
	 * The 'tr' program is written so
	 * that it will read bytes from stdin until there are no more
	 * bytes to read. Since it is actually reading from the pipe,
	 * there are no more bytes to read from the pipe when the write
	 * end of the pipe is closed. The write end will be closed when
	 * child1 exits---because the OS will ensure that stdin, stdout,
	 * stderr, and all other file descriptors are closed when every
	 * program exits.
	 *
	 * Therefore, child2 can only exit when child1 is finished. If
	 * both child1 and child2 ran "ls", then this assumption wouldn't
	 * be true because the second "ls" command will exit after
	 * printing to stdout---it doesn't read any thing from stdin, and
	 * it doesn't wait for stdin to be be closed by the writer before
	 * exiting.
	 */
	int status;
	waitpid(child2, &status, 0);
}
