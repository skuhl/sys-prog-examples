// Scott Kuhl
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// For more information about string literals, see:
// https://www.securecoding.cert.org/confluence/display/c/STR30-C.+Do+not+attempt+to+modify+string+literals
// http://programmers.stackexchange.com/questions/294748/why-are-c-string-literals-read-only
int main(void)
{
	// This will work fine, strdup() will malloc some space.
	char *str = strdup("Hello world");
	*str = 'X';
	printf("%s\n", str);
	free(str);

	// This will work fine, the array is initialized with contents of the string.
	char array[] = "Hello world";
	array[0] = 'X';
	printf("%s\n", array);

	if( 0 ) // CHANGE ME TO 1 to see the error this code causes!
	{
		// String literals are global and we shouldn't change them. For
		// example, if the same string literal appeared multiple times in
		// your program, the compiler may only put a single global string
		// in your code and refer to that string from multiple places.:
		char *literal = "Hello world";
		// A better way to declare this variable that would reduce the
		// chances of you making a mistake:
		// const char *literal = "Hello world";
		*literal = 'X'; // This MAY NOT WORK because we are changing the string literal itself!
		printf("%s\n", literal); // Might work, but is actually undefined.
	}

	if( 0 ) // CHANGE ME TO 1 to see the error this code causes!
	{
		char *mallocStr = (char*) malloc(256);
		// the following line makes the mallocStr pointer point to a
		// string literal. We shouldn't change or free() it.
		mallocStr = "Hello world";
		free(mallocStr); // WRONG!
	}


	// Try to check to see if the compiler is smart enough to store
	// this string once even though it is used in two places in this
	// program.
	char *literal1 = "This is a literal.";
	char *literal2 = "This is a literal.";
	if(literal1 == literal2) // compare the two pointers, see if they are the same
		printf("literal1 and literal2 point to the same address\n");
	else
		printf("literal1 and literal2 point to different addresses\n");
	
	
	return 0;
}
