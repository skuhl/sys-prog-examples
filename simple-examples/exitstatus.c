// Scott Kuhl

/* This example allows you to try using different exit status codes.

   Although C uses integers as return values, you will find that Linux
   only accepts values between 0 and 255. For example, if you return
   -1 the actual value returned will be 255. If you return 256, the
   actual value returned will be 0. I.e., the numbers wrap around.

   Also note that if a program is killed because of a signal, the exit
   status will be 128+N where N is the number of that signal. SIGINT=2
   is what happens when you press Ctrl+C. So every program that you
   Ctrl+C to exit should exit with the exit status of 128+2 = 130.

   The glibc manual recommends avoiding use of exit status values of
   128 or higher:

     "A general convention reserves status values 128 and up for
     special purposes. In particular, the value 128 is used to
     indicate failure to execute another program in a subprocess. This
     convention is not universally obeyed, but it is a good idea to
     follow it in your programs."
     - https://www.gnu.org/software/libc/manual/html_node/Exit-Status.html
   
   Note: You can also set the exit status by calling exit() and using
   the status code as the parameter.
 */
#include <stdio.h>

int main(int argc, char *argv[])
{
	int exitStatus = 0;

	if(argc < 2 || sscanf(argv[1], "%d\n", &exitStatus) != 1)
	{
		printf("Usage: %s exitStatus    - where exitStatus is an integer\n", argv[0]);
		printf("Returning %d\n", 1);
		return 1;
	}

	printf("Returning %d\n", exitStatus);
	printf("If you are using a bash-like shell, try running 'echo $?' immediately after you run this program to see the actual return value.\n");
	return exitStatus;
}
