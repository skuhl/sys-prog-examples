// Scott Kuhl
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

/* This function converts a string to a integer twice: once using
 * atoi() and once using strtol(). strtol() provides a way to check
 * for common problems. */
void print(char *buf)
{
	// Demonstrate converting string to int with atoi()
	//
	// Functions similar to atoi() include atof() atol() atoll()
	int result = atoi(buf);
	printf("atoi(\"%s\") --> %d\n", buf, result);


	// strtol() makes it easier to detect when errors occur. It also
	// allows us to convert numbers from different bases.
	//
	// Functions similar to strtol() include strtof() strtod() strtold() strtoul() strtoull() strtoll()
	
	errno = 0; // make sure errno is zeroed out.
	char *endptr; // tells us which character strtol stopped at
	long int lresult = strtol(buf, &endptr, 10);
	printf("strtol(\"%s\", NULL, 10) --> %ld\n", buf, lresult);

	// Check to see if any errors occurred when we called strtol()
	if(errno == ERANGE && (lresult == LONG_MAX || lresult == LONG_MIN))
		perror("strtol overflow/underflow");
	else if(errno == EINVAL)
		perror("strtol base contains unsupported value");
	else if(errno != 0)
		perror("strtol other error");
	if(endptr == buf)
		fprintf(stderr, "strtol didn't find any digits\n");

	printf("\n");
}

int main(void)
{
	print("10");

	// atoi() and strtol() accept arbitrary amounts of whitespace
	// before the number. Whitespace is identifed via isspace() (it
	// includes spaces, tabs, newlines, etc).
	print("\n \t 10");
	
	// atoi() and strtol() ignore trailing characters that are not numbers.
	print("10X");
	
	// atoi() usually returns 0 when presented with an invalid
	// number. strtol() allows us to recognize when this occurs.
	print("X10");

	// Plus/minus characters are handled by atoi() and strtol()
	print("+10");
	print("-10");

	// atoi() works on all ints (INT_MIN to INT_MAX)---but provides no
	// way to detect if overflow or underflow has occurred. strtol()
	// handles this case without any problem since it converts values
	// to a "long int", not an "int".
	char buffer[1024];
	snprintf(buffer, 1024, "%d", INT_MAX);
	print(buffer); // OK!
	snprintf(buffer, 1024, "%ld", ((long)INT_MAX)+1);
	print(buffer); // FAIL - You will see wraparound occur in the output!

	// largest number strtol() can handle:
	snprintf(buffer, 1024, "%ld", LONG_MAX);
	print(buffer);
	// strtol() DOES indicate when overflow/underflow occurs---and
	// doesn't wraparound the result.
	snprintf(buffer, 1024, "%lu", ((unsigned long)LONG_MAX)+1);
	print(buffer);

	return EXIT_SUCCESS;
}
