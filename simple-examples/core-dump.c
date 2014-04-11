// Scott Kuhl
//
// This program demonstrates how to create and use core dump files.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h> // For strlimit()

void enableCoreDump()
{
	/* Running "ulimit -c" from the command line will show you the
	 * maximum allowable core dump file size. Often, it defaults to 0
	 * bytes. You can change the value for a particular shell/console
	 * by running "ulimit -c unlimited". This code does the same
	 * thing in C: */
	printf("We are making sure that we can write a core dump file...\n");
	printf("(You could do this yourself by running 'ulimit -c unlimited' at the command line and 'ulimit -c' to see the current allowed max core size file.)\n");
	struct rlimit core_limits;
	core_limits.rlim_cur = core_limits.rlim_max = RLIM_INFINITY;
	setrlimit(RLIMIT_CORE, &core_limits);
}

int main(int argc, char* argv[])
{
	(void) argc; // hide compiler warning.
	enableCoreDump();
	printf("\n");
	printf("Getting ready to crash...\n");
	printf("If a core dump gets created, it will create a file named 'core' in the current directory.\n");
	printf("To debug using coredump file, run: gdb %s core\n", argv[0]);
	
	// pick a location in memory, start reading from it.
	ssize_t *x = (ssize_t*) 0xdeadbeef;
	int sum=0;
	while(1)
	{
		sum+=*x;
		x++;
	}
	printf("Sum: %d\n", sum);
	return 0;
}
