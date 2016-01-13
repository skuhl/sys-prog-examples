// Scott Kuhl
// Code is largely inspired by:
// http://741mhz.com/signal-handler/
// Also see:
// https://www.securecoding.cert.org/confluence/pages/viewpage.action?pageId=3903

#define _GNU_SOURCE
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

volatile sig_atomic_t unprocessedSig = 0;


/* Note: Our signal handler can get interrupted with other signals. We
 * should only call async-signal-safe functions, or simply do as
 * little work as we can inside of our signal handler. */
void sighandler(int signo)
{
	if(signo == SIGINT)
		unprocessedSig=1;
}

int main(void)
{
	printf("This is pid %d\n", getpid());

	/* sigaction is a struct describing a signal handler. It contains:
	   - A signal handler function
	   
	   - A signal mask which specifies which signals should be blocked
         while the signal handler function is running. If the signal
         handler returns normally, the original signal mask will be
         restored. To understand signal masks, see sigprocmask.c
	   
	   - A set of flags.
	*/
	struct sigaction act;
	
	/* Specify the signal handler function to be called when one of
	 * the specified signals occur. */
	act.sa_handler = &sighandler;

	/* Add all of the signals to the signal mask set. This means that
	   all signals will be blocked (i.e., delayed) while our signal
	   handler function is running. The original signal mask will be
	   restored when our signal handler exits normally. */
	sigfillset(&act.sa_mask);
	
	/* If the signal handler gets run in the middle of some function
	 * calls (such as open(), read(), or write()) and the signal
	 * handler returns normally, there are couple of options: return a
	 * failure code EINTR from those functions, or try to resume the
	 * function. With SA_RESTART, the function is resumed instead of
	 * returning an error. */
	act.sa_flags = SA_RESTART;
	
	/* Add our signal handler to SIGINT (i.e., Ctrl+C) */
	if(sigaction(SIGINT, &act, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}

	printf("IMPORTANT: Kill this process by running 'killall -9 sigaction' in another terminal window.\n");
	
	while(1)
	{
		if(unprocessedSig)
		{
			unprocessedSig = 0;
			printf("SIGINT signal occurred.\n");
		}
	}
}
