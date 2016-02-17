// Scott Kuhl

/* Each terminal has a 'device' associated with it that we can read
   from and write to. Run "tty" to find the filen that corresponds
   with the device for your terminal.

   In this example, open two terminals on the same machine. Run this
   program in one of them. When prompted, enter the device for the
   other terminal.

   Then, this program uses dup2() to make standard in, standard error,
   and standard out for this program point to the other terminal
   instead.

   It might not work so well to try to read from stdin of the other
   terminal because the shell running in that other terminal is also
   trying to read from it. But, you can try to work around this. Try
   running "sleep 10" in the other terminal an see if you can then
   read from stdin correctly from the other terminal
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main(void)
{
	printf("Run 'tty' command in a different terminal than this one.\n");
	printf("Type in what it prints out here (example: /dev/pts/17 or /dev/ttys000):\n");
	char termDev[256];
	fgets(termDev, 256, stdin);
	// remove newline
	for(unsigned int i=0; i<strlen(termDev); i++)
		if(termDev[i] == '\n')
			termDev[i] = '\0';
	printf("You entered %s\n", termDev);
	
	/* Redirect standard in, out, and error to another terminal */
	int fd = open(termDev,O_RDWR);
	if( fd != -1 )
	{
		// dup2() returns -1 and sets errno on error, we aren't checking that.
		dup2(fd,0); // We could use STDIN_FILENO instead of 0
		dup2(fd,1); // We could use STDOUT_FILENO instead of 1
		dup2(fd,2); // We could use STDERR_FILENO instead of 2
		// The dup2() lines above say that we need ot take stdin,
		// stdout, and stderr all point to this file descriptor that
		// we can read/write to.
		

		// We don't need the fd we opened any more. We already set up
		// the other things to send to it. Its file descriptor should
		// be greater than 2.
		if(fd > 2)
		{
			printf("Closing file descriptor %d\n", fd);
			close(fd);
		}
	}
	else
		perror("open");

	printf("Type in a string:\n");
	char buf[100];
	if(fgets(buf, 100, stdin) == NULL)
		printf("Error in fgets()");
	else
		printf("buf=%s\n", buf);
}
