// Scott Kuhl
#include <stdio.h>
#include <limits.h>

int main(void)
{
	// Overflowing an int:
	printf("INT_MAX + 1  = %d\n", INT_MAX+1); // undefined

	// The smallest negative number has no corresponding positive
	// number.
	printf("INT_MIN * -1 = %d\n", INT_MIN*-1); // undefined

	// What is the worst that can go wrong when undefined behavior
	// occurs?  The C FAQ indicates that *anything* could happen when
	// a program when undefined behavior occurs. For more info, see:
	// http://blog.regehr.org/archives/213
	
	/* For comprehensive information for avoiding these problems, see
	   the following links:

	   Signed ints: https://www.securecoding.cert.org/confluence/display/seccode/INT32-C.+Ensure+that+operations+on+signed+integers+do+not+result+in+overflow

	   Unsigned ints: https://www.securecoding.cert.org/confluence/display/seccode/INT30-C.+Ensure+that+unsigned+integer+operations+do+not+wrap

	 */
	
	
}
