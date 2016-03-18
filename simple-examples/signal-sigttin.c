// Scott Kuhl

/* The SIGTTIN signal is generated when a process tries to read from a
 * terminal but is running in the background. The program will be
 * resumed (with a SIGCONT signal) once it is able to send read from
 * the terminal successfully (i.e., it is placed in the foreground
 * again).
 *
 * TRY THIS: Run this program normally.
 *
 * ALSO TRY THIS: Then, try running this program by putting it in the
 * background. Most shells allow you to do this with the command
 * "./signal-sigttin &". You should see that the shell pauses the
 * program when it tries to read from stdin.  You can resume the
 * program by running "fg". You will then be able to type something at
 * the prompt.
 *
 * This program uses a signal handler so you can see that the SIGTTIN
 * and SIGCONT signals get sent as expected.
 */

// Note that _GNU_SOURCE changes the behavior of signal(). See 'man signal' for more information.
#define _GNU_SOURCE
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sighandler(int signo)
{
	if(signo == SIGTTIN)
		printf("Handler executed for signal %d (SIGTTIN)\n", signo);
	else if(signo == SIGCONT)
		printf("Handler executed for signal %d (SIGCONT)\n", signo);
	else
		printf("Handler executed for signal %d\n", signo);
		
	printf("Executing default signal handler for signal.\n");
	signal(signo, SIG_DFL); // reset signal handler to default
	raise(signo);
}

int main(void)
{
	/* See signal.c for detailed information describing a variety of
	 * details you should be aware of regarding signals. */
	signal(SIGTTIN, sighandler);
	signal(SIGCONT, sighandler);


	/* Keep trying to read from stdin until we are successful. */
	int keepTrying = 1;
	while(keepTrying)
	{
		printf("Type something:\n");
		
		char buf[100];
		if(fgets(buf, 100, stdin) == NULL)
			printf("fgets error\n");
		else
		{
			printf("I read: %s\n", buf);
			keepTrying = 0;
		}
	}

	return 0;
}
