// Scott Kuhl

/* Illustrates how to use pause() */

#include <unistd.h>
#include <stdio.h>
#include <signal.h>


void sighandler(int signo)
{
	// See signal.c and signal-better.c for a more comprehensive
	// example of handling signals.
	printf("In signal handler.\n");
}

int main(void)
{
	printf("Pausing until we receive a signal.\n");
	printf("This process has pid %d\n", getpid());

	signal(SIGUSR1,  sighandler); // set up a signal handler
	
	/* Pause causes us to sleep until...:

	   - LINUX: "a signal is delivered that either terminates the
	   process or causes the invocation of a signal catching function"

	   - OSX: pause() returns "upon termination of a signal handler
         that is started during a pause()."
	*/
	pause(); // it is better to use sigsuspend() instead, see sigsuspend.c

	/* For a description of why pause() is not ideal, see:
	   http://stackoverflow.com/questions/6328055/whats-the-problem-of-pause-at-all
	*/

	printf("Returned from pause(), exiting.\n");
	return 0;
}
