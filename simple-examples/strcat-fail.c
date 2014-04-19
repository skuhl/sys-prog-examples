// Scott Kuhl
//
// This program contains a bug. Your compiler may not print a warning
// (even with -Wextra). It might run without crashing. It might print
// "hello world" (or might not). cppcheck and valgrind might (or might
// not) detect this problem. It might run differently depending on if
// you compile it with -g and/or -O2. Turning on more optimization may
// help the compiler detect the error.
//
// See: http://sourceforge.net/apps/trac/cppcheck/ticket/4241
#include <stdio.h>
#include <string.h>

int main(void)
{
	char str[80] = "hello worl";
	char d='d';
	/* Including this line in your code might make a valgrind error go
	 away---because the compiler might put 'n' after 'd' in memory and
	 Valgrind would then think that reading either of these bytes
	 would be OK since they are part of your program. */
	// char n='\0';

	strcat(str,&d); // WRONG.
	/* The d variable is not a null terminated string. Therefore,
	   strcat can't figure out when to stop copying from d into
	   str. The str string stored in the char array is
	   null-terminated. */
	puts(str);
	return 0;
}
