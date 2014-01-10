// Scott Kuhl
//
// This program does not check the return code of close(), dup2(),
// execlp(), fork(), and waitpid(). A good program would add those
// additional checks!
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define READ_END 0
#define WRITE_END 1

int main (void)
{
	int fd[2];
	pipe(fd);

	int child1 = fork();
	if(child1 == 0) /* we are child 1 */
	{
		// we will be writing to the pipe, no need to read:
		close(fd[READ_END]);
		// Make the fd for our pipe have the same fd number as stdout:
		dup2(fd[WRITE_END], STDOUT_FILENO);
		execlp("ls", "ls", "-al", NULL);
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
	}
	/* Only parent gets here. If parent doesn't close the WRITE_END of
	 * the pipe, then child2 might not exit because the parent could
	 * still write data into the pipe that child2 is reading from. */
	close(fd[READ_END]);
	close(fd[WRITE_END]);

	int status;
	waitpid(child2, &status, 0);
}
