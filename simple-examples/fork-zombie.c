// Scott Kuhl

/* When fork() is called, the the programmer expects that they can
   call wait() in the parent and get access to the exit code of the
   child process. A zombie process is a child process that has exited,
   but the parent hasn't called wait() yet. So, the child process
   remains in a zombie state which has basic information about the
   child process (its exit status, etc). Once wait() is called, the
   zombie process exits.

   In this example, we never call wait(). However, the zombie process
   will be killed once the parent process exits.

   See: https://en.wikipedia.org/wiki/Zombie_process
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(void)
{
	pid_t pid = fork();
	if(pid == 0)
	{
		printf("CHILD (pid %d): It was nice knowing you, parent. I'm done.\n", getpid());
		exit(EXIT_SUCCESS);
	}
	else
	{
		printf("PARENT (pid %d): Started.\n", getpid());
		printf("PARENT: Starting infinite loop. Press Ctrl+C to exit.\n");
		printf("Use 'ps' to see the zombie process\n");
		while(1)
		{
			sleep(1);
		}
	}
}
