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
	struct sigaction act;
	act.sa_handler = &sighandler;
	act.sa_flags = 0;
	if(sigemptyset(&act.sa_mask) != 0)
	{
		printf("sigemptyset error\n");
		exit(EXIT_FAILURE);
	}
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
