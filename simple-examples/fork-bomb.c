// Scott Kuhl
// See: http://en.wikipedia.org/wiki/Fork_bomb
#include <unistd.h>
#include <stdio.h>

int main(void)
{
	printf("Only run this program if you can reboot the computer that you are running it on. Preferably run it on your own computer---not a computer administered by someone else.\n\n");
	printf("Even if running 'limit' on the command line shows a cap on the maximum number of processes you can run, a fork bomb may make it difficult for you to run other processes (such as 'killall') to kill the process.\n");
	printf("\n");
	printf("You have been warned.\n");
	printf("\n");
	printf("Press Ctrl+C if you don't want to run a fork bomb on this machine.\n");
	printf("Press any other key to (probably) crash this machine.\n");
	char buf[100];
	fgets(buf, 100, stdin);
	
	/* We aren't checking the return value of fork(), but in the case
	 * of a fork bomb run on a system where the number of processes
	 * has been capped, it is possible that fork() would return -1 to
	 * indicate an error and fail to actually fork. */
	
	while(1)
		fork();

}
