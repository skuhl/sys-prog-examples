// Scott Kuhl
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Compilers can rely on "const" keywords to help with
   optimization. It can also help you write better code and have the
   compiler notify you of potential problems. */

/* Although this example program only demonstrates using the const
   keyword for function parameters and pointers, the const keyword can
   also be used when variables are declared elsewhere in your
   program. */

/* In this function, we are not allowed to change the data that the
 * str pointer points to. We can, however, make the str variable point
 * to a different location entirely. */
void changeToX(const char *str)
{
	// This will produce a compiler error/warning:
	printf("before change: %s\n", str);
	// TRY UNCOMMENTING THE LINE BELOW:
	// *str = 'X'; // change first byte of char to an X
	printf("after change: %s\n", str);

	str = "X"; // Here, we make str point to a string literal. This is
			   // allowed because we aren't changing the data that the
			   // original str pointer pointed at.
}

/* Note that we have changed the order of 'const', 'char', and '*' in
 * the parameter listing. In this case, the str pointer is constant
 * but the data that it points to is not. */
void changeToX2(char * const str)
{
	*str = 'X'; // OK because str still points to the same place.

	// TRY UNCOMMENTING THE LINE BELOW:
	// str = "X"; // not allowed because it makes the str pointer point a string literal.
}

/* In this version, we can't change the pointer or change the data
 * that the pointer points to. */
void changeToX3(const char * const str)
{
	printf("changeToX3(): %s\n", str);
	
	//*str = 'X'; // not allowed.
	//str = "X"; // not allowed.
}


int main(void)
{
	// strdup() will malloc some space. str could be changed since it
	// is not a string literal. See modify-string-literal.c
	char *str = strdup("Hello world");
	changeToX(str);
	changeToX2(str);
	changeToX3(str);
	free(str);

	return 0;
}
