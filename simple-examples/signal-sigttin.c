/* The SIGTTIN signal is generated when a process tries to read from a
 * terminal but is running in the background. If you run this program
 * in the background with your shell, you will see the program receive
 * the SIGTTIN signal and then the program will call the default
 * SIGTTIN signal handler which will pause your program. When the
 * process is continued, it should read successfully from fgets(). */

// Note that _GNU_SOURCE changes the behavior of signal(). See 'man signal' for more information.
#define _GNU_SOURCE
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sighandler(int signo)
{
	printf("Handler executed for signal %d\n", signo);

	printf("Executing default signal handler for signal.\n");
	signal(signo, SIG_DFL); // reset signal handler to default	
	kill(getpid(), signo);
}

int main(void)
{
	signal(SIGTTIN, sighandler);
	signal(SIGCONT, sighandler);
	printf("Type something...\n");
	char buf[100];
	if(fgets(buf, 100, stdin) == NULL)
		printf("fgets error.\n");
	else
		printf("I read: %s\n", buf);
	return 0;
}
