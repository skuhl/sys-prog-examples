// Scott Kuhl
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// We have declared the pointer to be constant, so we are not allowed
// to change anything that it points to. Similarly, if we added a
// parameter "const int i", we wouldn't be able to change that
// either. Compilers can rely on "const" keywords to help with
// optimization. It can also help you write better code and have the
// compiler notify you of potential problems.
void changeToX(const char *str)
{
	// This will produce a compiler error/warning:
	printf("before change: %s\n", str);
	// TRY UNCOMMENTING THE LINE BELOW:
	// *str = 'X'; // change first byte of char to an X
	printf("after change: %s\n", str);
}

int main(void)
{
	// strdup() will malloc some space. str could be changed since it
	// is not a string literal. See modify-string-literal.c
	char *str = strdup("Hello world");
	changeToX(str);
	free(str);

	return 0;
}
