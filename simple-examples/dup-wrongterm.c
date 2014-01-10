// Scott Kuhl

/* The owner of a terminal can read and write directly to that
 * terminal. Run "ps" to find the name of your terminal (for example,
 * pts/0) and change the code so that it writes to it. No matter which
 * terminal you run the program in, it will send stdin and stdout to
 * one specific terminal. Reading from stdin may not work reliably
 * because the shell and your program are trying to read from it. But,
 * if you run "sleep 10" or similar in the terminal that the IO is
 * happening in, you should then be able to read from stdin
 * correctly. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(void)
{
	/* Redirect standard files to another terminal */
	int fd = open("/dev/pts/0",O_RDWR);
	if( fd != -1 )
	{
		dup2(fd,0);
		dup2(fd,1);
		dup2(fd,2);
		if(fd > 2)
			close(fd);
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
