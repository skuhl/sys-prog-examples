// Scott Kuhl

/* This program is intended to show how process group IDs work and how
 * other process groups are in the "background". By commenting using
 * different kill() calls at the bottom of this program, you can
 * explore this behavior. */


#define _GNU_SOURCE
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void sighandler(int signo)
{
	printf("pid=%d received signal %d, exiting.\n", getpid(), signo);
	exit(EXIT_SUCCESS);
}

void processInfo(char *msg)
{
	pid_t pgid = getpgid(getpid());
	if(pgid == -1)
		perror("getpgid error:");
	pid_t sid = getsid(0);
	if(sid == -1)
		perror("getsid error:");

	printf("%s: This is %d in session %d (created from %d); pgid=%d\n",
	       msg, getpid(), sid, getppid(), pgid);
}


int main(void)
{
	signal(SIGUSR1, sighandler);
	processInfo("main");

	// Start two child processes which sleep for 4 seconds and then
	// exit.
	int f = fork();
	if(f < 0)
		perror("fork error:");
	else if(f == 0) /* child */
	{
		processInfo("child1");
		sleep(5);
		printf("child1 exiting\n");
		exit(EXIT_SUCCESS);
	}

	f = fork();
	if(f < 0)
		perror("fork error:");
	else if(f == 0) /* child */
	{
		processInfo("child2");
		sleep(5);
		printf("child2 exiting\n");
		exit(EXIT_SUCCESS);
	}

	/* Fork another process. */
	f = fork();
	if(f < 0)
		perror("fork error:");
	else if(f == 0) /* Create a new process (child3) that will also
	                 * spawn off two children. */
	{
		if(setpgid(0, 0) == -1) // make child3 a new process group.
			perror("setpgid error:");
		processInfo("child3");

		/* make child3 process spawn off two more children. These
		 * children will be in the same progress group as child3 is
		 * in */
		f = fork();
		if(f < 0)
			perror("fork error:");
		else if(f == 0) /* child */
		{
			processInfo("child3-1");
			sleep(10);
			printf("child3-1 exiting\n");
			exit(EXIT_SUCCESS);
		}

		f = fork();
		if(f < 0)
			perror("fork error:");
		else if(f == 0) /* child */
		{
			processInfo("child3-2");
			sleep(10);
			printf("child3-2 exiting\n");
			exit(EXIT_SUCCESS);
		}
		sleep(1);

		/* Send a signal to child3; child3-1 and child3-2 will still survive. */
		// kill(getpid(), SIGUSR1);

		/* Send a signal to all processes in the child3 process group. This should kill child3, child3-1, child3-2. */
//		kill(0, SIGUSR1); // signal to all processes in this process's group
		wait(NULL); // wait for child3-1
		wait(NULL); // wait for child3-2

		printf("child3 exiting\n");
		exit(EXIT_SUCCESS);
	}

	sleep(1);
//	kill(0, SIGUSR1); // signal to all processes in this process's group; should kill main, child1, child2
	wait(NULL); // wait for child1
	wait(NULL); // wait for child2
	wait(NULL); // wait for child3
	printf("main exiting\n");
}
