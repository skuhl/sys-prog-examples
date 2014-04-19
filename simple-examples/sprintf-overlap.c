// Scott Kuhl
//
// Using sprintf() to concatenate text onto a string in-place is
// incorrect. Use strcat() or strncat() instead.

/* From 'man 3 sprintf':

C99 and POSIX.1-2001 specify that the results are undefined if a call
to sprintf(), snprintf(), vsprintf(), or vsnprintf() would cause
copying to take place between objects that overlap (e.g., if the
target string array and one of the supplied input arguments refer to
the same buffer). See NOTES.

NOTES
Some programs imprudently rely on code such as the following

sprintf(buf, "%s some further text", buf);

to append text to buf.  However, the standards explicitly note that
the results are undefined if source and destination buffers overlap
when calling sprintf(), snprintf(), vsprintf(), and vsnprintf().
Depending on the version of gcc(1) used, and the compiler options
employed, calls such as the above will not pro‐ duce the expected
results.

The glibc implementation of the functions snprintf() and vsnprintf()
conforms to the C99 standard, that is, behaves as described above,
since glibc version 2.1.  Until glibc 2.0.6 they would return -1 when
the output was truncated.

 */
#include <stdio.h>
#include <string.h>

int main(void)
{
	char buffer[12] = "hello";
	int ret = sprintf(buffer, "%s world", buffer); // error here
	if(ret > 0)
		printf("sprintf wrote %d chars\n", ret);
	else
		printf("sprintf error\n"); // We aren't told about error

	// May or may not print what we want it to:
	printf("Buffer contents: %s\n", buffer);
	
	sprintf(buffer, "world");
	ret = sprintf(buffer, "hello %s", buffer); // error here
	if(ret > 0)
		printf("sprintf wrote %d chars\n", ret);
	else
		printf("sprintf error\n"); // We aren't told about error

	// May or may not print what we want it to:
	printf("Buffer contents: %s\n", buffer);

	// See strncat.c for a better way to do this.
	return 0;
}
