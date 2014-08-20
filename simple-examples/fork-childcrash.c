// Scott Kuhl
//
// When a child process crashes, you might not be notified of the
// crash like you normally would with a single process program.

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>

int main(void)
{
	pid_t pid = fork();
	if(pid==0)
	{
		printf("Child created...\n");

		int typeOfExit = 0; // TRY CHANGING THIS!
		if(typeOfExit == 0)
		{
			int i = 1 / 0; // floating point exception
			printf("i is %d\n", i);
		}
		else if(typeOfExit == 1)
			raise(SIGSEGV); // segfault
		else if(typeOfExit == 2)
			abort();
		else if(typeOfExit == 3)
			exit(42);

		printf("Child is exiting. THIS SHOULDN'T GET PRINTED OUT!\n");
		exit(EXIT_SUCCESS);    
	}
	else if(pid > 0)
	{
		printf("Waiting for child\n");
		int status;
		pid_t ret = wait(&status);
		if(ret == -1)
			perror("wait");
		if(WIFEXITED(status))
			printf("Child exited NORMALLY with return value %u\n",
			       WEXITSTATUS(status));
		else if(WIFSIGNALED(status))
			printf("Child was terminated due to an UNHANDLED SIGNAL %u and returned %u\n",
			       WTERMSIG(status), WEXITSTATUS(status));
		else if(WIFSTOPPED(status))
			// not possible in many circumstances, see "man wait" for more info.
			printf("Child was STOPPED by signal %u\n",
			       WSTOPSIG(status));
		else
			// Note: There are other cases that could be handled, see "man
			// wait"
			printf("Other error.\n");

	}
	else // pid == -1
	{
		perror("fork"); // fork failed
		exit(EXIT_FAILURE);
	}
}
