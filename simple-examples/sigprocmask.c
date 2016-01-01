// Scott Kuhl

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h> // getpid()

/* Iterates through a list of signals and prints out which signals are in a signal set. */
void printSignalSet(sigset_t *set)
{
	/* This listing of signals may be incomplete. */
	const int sigList[] = { SIGHUP, SIGINT, SIGQUIT, SIGILL,
	                        SIGABRT, SIGFPE, SIGKILL, SIGSEGV,
	                        SIGPIPE, SIGALRM, SIGTERM, SIGUSR1,
	                        SIGUSR2, SIGCHLD, SIGCONT, SIGSTOP,
	                        SIGTSTP, SIGTTIN, SIGTTOU };
	const char *sigNames[] = { "SIGHUP", "SIGINT", "SIGQUIT", "SIGILL",
	                           "SIGABRT", "SIGFPE", "SIGKILL", "SIGSEGV",
	                           "SIGPIPE", "SIGALRM", "SIGTERM", "SIGUSR1",
	                           "SIGUSR2", "SIGCHLD", "SIGCONT", "SIGSTOP",
	                           "SIGTSTP", "SIGTTIN", "SIGTTOU" };
	const int sigLen = 19;
	
	for(int i=0; i<sigLen; i++)
	{
		int ret = sigismember(set, sigList[i]);
		if(ret == -1)
		{
			perror("sigismember:");
			exit(EXIT_FAILURE);
		}
		else if(ret == 1)
		{
			printf("Signal %s=%d IS masked.\n", sigNames[i], sigList[i]);
		}
		else
		{
			printf("Signal %s=%d is not masked.\n", sigNames[i], sigList[i]);
		}
	}
}


int main()
{
	/* Each process inherits its parents signal mask. The signal mask
	 * specifies which set of signals are currently blocked. Signals
	 * that are blocked are held by the operating system and will be
	 * delivered later.
	 *
	 * http://www.gnu.org/software/libc/manual/html_node/Blocking-Signals.html
	 */

	sigset_t set; // To change or see the contents of this set, see:
	// http://www.gnu.org/software/libc/manual/html_node/Signal-Sets.html


	/* Retrieve the current set of masked signals sigprocmask() and
	   store them in 'set'. From the Linux man page:

	   int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
	   
	   If set is NULL, then the signal mask is unchanged (i.e., how is
       ignored), but the current value of the signal mask is nevertheless
       returned in oldset (if it is not NULL).
	*/
	if(sigprocmask(0, NULL, &set) != 0)
	{
		perror("sigprocmask:");
		exit(EXIT_FAILURE);
	}

	printf("--- Initial signal mask for this process: ---\n");
	printSignalSet(&set);


#if 1
	sigaddset(&set, SIGINT); // Add SIGINT to our set
	/* Tell OS that we want to mask our new set of signals---which now includes SIGINT. */
	if(sigprocmask(SIG_SETMASK, &set, NULL) != 0)
	{
		perror("sigprocmask:");
		exit(EXIT_FAILURE);
	}

	/* Now, SIGINT will be "blocked". */
	printf("--- NEW signal mask for this process: ---\n");
	printSignalSet(&set);
#endif



	int secToSleep = 20;
	printf("Try Ctrl+C. Try killing this program with 'kill -kill %d'. Going to sleep for %d seconds.\n", getpid(), secToSleep);
	sleep(secToSleep);
	printf("Sleep returned.\n");

	
	/* If SIGINT was blocked and the user pressed Ctrl+C during the
	 * sleep above, that SIGINT signal is just blocked. By unmasking
	 * that signal, the blocked SIGINT will be delivered. */
	printf("Removing all signals from mask.\n");
	sigemptyset(&set);
	if(sigprocmask(SIG_SETMASK, &set, NULL) != 0)
	{
		perror("sigprocmask:");
		exit(EXIT_FAILURE);
	}

	/* If you pressed Ctrl+C during the sleep, the SIGINT should be
	 * processed here. This means that the following message wouldn't
	 * be printed at all because SIGINT would cause the program to
	 * exit instead of us reaching the end of main() */
	sleep(1);
	printf("Exited normally.\n");
	return 0;
}
