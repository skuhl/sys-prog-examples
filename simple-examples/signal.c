// Scott Kuhl
//
// Use sigaction() instead of signal()! Even "man 2 signal" says at
// the top of the file (in bold) that signal() should be avoided and
// that sigaction() should be used instead.
//
// This example is here for informational purposes only. If you are
// writing production code, see signal-better.c or sigaction.c for a
// better example.


#define _GNU_SOURCE
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>



void sighandler(int signo)
{
	/* Important: This signal handler is incorrect. Our signal handler
	 * function should only call async-signal-safe functions as
	 * described in "man 7 signal". The manual clearly states: "If a
	 * signal interrupts the execution of an unsafe function, and
	 * handler calls an unsafe function, then the behavior of the
	 * program is undefined. */

	// printf() is NOT an async-signal-safe function.
	printf("Handler executed for signal %d\n", signo);

	/* Another important note: A signal can occur when another signal
	 * is still being processed! */
}

int main(void)
{
	// Note: From "man signal" page: "Using signal() in a
	// multithreaded process is unspecified" (i.e., anything could
	// happen, including a crash).

	if(signal(SIGINT,  sighandler) == SIG_ERR || // interrupt, ctrl+c
	   signal(SIGSEGV, sighandler) == SIG_ERR || // segfault
	   signal(SIGTERM, sighandler) == SIG_ERR)   // terminate
		printf("Failed to set up one or more signal handlers\n");
	// This code only handles a few signals---there are many more
	// signals we could handle.
	
	printf("IMPORTANT: Kill this process by running 'killall -9 signal' in another terminal window.\n");

	while(1)
	{
		printf("Sleeping for a while...\n");
		sleep(10);
	}

	// intentionally cause seg fault:
	// int *p = NULL;
	// printf("%d\n", *p); // ... movl (%rax), %esi ...
	return 0;
}
