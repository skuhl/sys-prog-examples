// Scott Kuhl

/* When fork() is called, is is possible for the parent process to
   exit before a child process. The remaining child process has no
   parent---and is therefore a "orphan" process.

   https://en.wikipedia.org/wiki/Orphan_process
*/

#include <stdio.h>     // needed for printf()
#include <stdlib.h>    // needed for exit()
#include <unistd.h>    // needed for fork()
#include <sys/types.h> // needed for for pid_t (Linux)

int main(void)
{
	pid_t pid = fork();
	if(pid == 0)
	{
		printf("CHILD: I am pid %d; my parent is pid %d\n", getpid(), getppid());
		sleep(2);
		printf("CHILD: I should be an orphan now.\n");
		printf("CHILD: My parent pid is %d\n", getppid());
		printf("CHILD: I'm exiting now.\n");
		exit(EXIT_SUCCESS);
	}
	else
	{
		sleep(1); /* sleep for a second to ensure that child has chance
		             to call getppid() before we exit. */
		printf("PARENT: Child, I'm out of here. You are on your own.\n");
		exit(EXIT_SUCCESS);
	}
}
