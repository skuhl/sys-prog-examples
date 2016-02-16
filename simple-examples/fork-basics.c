// Scott Kuhl

/* fork() allows you to create a copy of an existing process. It is a
   POSIX function and is how all processes are made on Unix systems.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   // needed for fork()
#include <sys/wait.h> // needed for wait()
#include <sys/types.h> // needed for pit_t (on Linux)
#include <signal.h>   // need for raise()

int main(void)
{
	printf("Begin. This is PID: %d\n", getpid());

	// pid_t is basically like an int---but it might be a different size.
	printf("pid_t is %zu bytes\n", sizeof(pid_t));
	pid_t forkReturn = fork();
	if(forkReturn == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if(forkReturn == 0)
	{
		printf(" CHILD: I have PID %d\n", getpid());
		sleep(1);
		printf(" CHILD: I am exiting.\n");

		/* Try each of these: */
		// exit(45); // exit status
		// return 67; // alternate way to exit
		// abort(); // exit due to a signal
		// raise(SIGSEGV); // simulate sigfault
		exit(EXIT_SUCCESS);
	}
	else // forkReturn > 0 and forkReturn is the PID of the child.
	{
		printf("PARENT: I have PID %d\n", getpid());
		printf("PARENT: My child has PID %d\n", forkReturn);
		printf("PARENT: It is good practice to wait for child to exit.\n");
		printf("PARENT: Waiting...\n");

		// TRY THIS:
		//  - What if you comment out wait()?
		//  - What if you wait() before you call fork()?
		int childStatus = 0;
		if(wait(&childStatus) == -1) 
		{
			perror("wait");
			exit(EXIT_FAILURE);
		}
		
		/* childStatus contains the exit status (8 bits) and other
		 * information too. */

		if(WIFEXITED(childStatus))
			printf("PARENT: The child exited NORMALLY with return value %u\n",
			       WEXITSTATUS(childStatus));
		
		else if(WIFSIGNALED(childStatus))
			printf("PARENT: The child was terminated due to an UNHANDLED SIGNAL %u\n",
			       WTERMSIG(childStatus));
		
		else if(WIFSTOPPED(childStatus))
			// not possible in many circumstances, see "man wait" for more info.
			printf("PARENT: Child was STOPPED by signal %u\n",
			       WSTOPSIG(childStatus));
		
		else
			// Note: There are other cases that could be handled, see "man
			// wait"
			printf("Other error.\n");

	}
}
