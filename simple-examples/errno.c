// Scott Kuhl
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <errno.h>
/*
  Many functions in C return a special value if an error
  occurred. However, many functions also set a variable called "errno"
  that contains detailed information about exactly what the error
  is. For example, open() will return -1 if an error occurs. If you
  want to identify the exact error, you can look at the errno
  variable. "man 2 open" indicates that it could be set to EACCES,
  EEXIST, EFAULT, EFBIG, EINTR, etc. To convert an errno integer into
  a human-readable string, use strerror() or perror().

  Each errno can be interpreted several different ways:
  - The errno itself is an integer.

  - There are preprocessor macros/variable names so you don't have to
    remember the numbers (EACCESS, EEXIST, etc). The way the numbers
    are assigned to these For a list of these, see "man 3 errno". It
    is best to rely on these variable names instead of the integer
    values themselves because different machines may use different
    integers for the same error.

  - The macro/variable names can also be mapped to a human readable
    message. These messages are also listed in "man 3 errno". These
    are the messages that perror() or strerror() print out.

  To get a quick idea of how the integers map to the variable names on
  your computer, try running:
  cpp -dM /usr/include/errno.h | grep 'define E' | sort -n -k 3
  // From: http://stackoverflow.com/a/503920/474549

  If you are running Ubuntu, you can install the "errno" package using
  the package manager and then run "errno -l" and get a list of the
  variables, integers, and strings.

  On my Linux machine, /usr/include/errno.h includes
  /usr/include/x86_64-linux-gnu/bits/errno.h which includes
  /usr/include/linux/errno.h which includes /usr/include/asm/errno.h
  which includes /usr/include/x86_64-linux-gnu/asm/errno.h which
  includes /usr/include/asm-generic/errno.h (includes some error
  codes 35-133) which includes /usr/include/asm-generic/errno-base.h
  (includes error codes 1-34).
 
*/


/*
 Using "extern" is one way to get access to the errno
 variable. However, "man errno" indicates that this is the wrong
 way. The recommended way to access errno is to #include <errno.h> to
 it.
*/
// extern int errno; // WRONG!

int main(void)
{
// NOTE: open() doesn't return errno, it sets it!
	int fd = open("/this/does/not/exist", O_RDONLY, 0644 );
	if( fd == -1 )
	{
		printf("errno=%d\n", errno);
		if(errno == EACCES)
		{
			// Two ways to print a nice error message based on the errno.
			perror( "EACCES error in open" );
			printf( "EACCES error in open: %s\n", strerror( errno ) );
		}
		else
		{
			perror( "Other error in open" );
			printf( "Other error in open: %s\n", strerror( errno ) );
		}
	}

	// errno starts the program set to 0 ("success"). Many functions
	// will *not* set it to 0 if successful (although some
	// might). For one description of the reasoning behind this, see:
	// http://programmers.stackexchange.com/questions/209729/
	perror("Perror1");
	fd = open("/dev/null", O_WRONLY, 0644 );
	if(fd > 0)
	{
		printf("open() was successful.\n");
		perror("Perror2"); //open() might not set errno back to success!
	}

	// You can assign values to errno in a thread-safe way:
	// http://stackoverflow.com/questions/1694164/is-errno-thread-safe
	errno = 1;
	perror("Perror3");

	return EXIT_SUCCESS;
}
