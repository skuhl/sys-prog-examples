/* Scott Kuhl

   This program prints a message if stdin is associated with a terminal or not. Try running this program two ways:

   "./isatty" will indicate that you are running it in a terminal.

   "ls | ./isatty" will indicate that stdin is not associated with a
   terminal (in this case, it is associated with a pipe!).

   "./isatty > file.txt" will indicate that stdout is not associated
   with a terminal (in this case, it is associated with a file!).

   
   An example of one program that uses information like this is
   "ls". If you run "ls" on the command line, you will usually get a
   listing of files organized into columns. But, if you run "ls |
   cat", files will be listed one-per-line to allow you to more easily
   sort, grep, etc. the output.
*/

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <errno.h>

void checktty(int fd, const char *name)
{
	if(isatty(fd)==0)
	{
		if(errno == EINVAL || errno == ENOTTY)
			printf("%s is not a terminal.\n", name);
		else
		{
			printf("%s\n", name);
			perror("isatty");
		}
	}
	else
		printf("%s is a terminal.\n", name);
}


int main(void)
{
	checktty(STDIN_FILENO,  "stdin");
	checktty(STDOUT_FILENO, "stdout");
	checktty(STDERR_FILENO, "stderr");
}
