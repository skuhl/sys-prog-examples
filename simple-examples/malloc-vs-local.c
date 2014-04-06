// Scott Kuhl
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* stringMalloc(void)
{
	// if we use malloc, the string is guaranteed to exist until we
	// call free(). Although all malloc()'d memory will be free'd when
	// the program exits, it is good to get into the habit of freeing
	// it since long-running programs that malloc() without free() may
	// use more and more memory (i.e., a memory leak).
	char* str = malloc(sizeof(char)*32);
	strcpy(str, "Hello world"); // copy string into the newly allocated memory.
	return str;
}

char *stringLiteral(void)
{
	// This is a string literal and it will have a global scope. They
	// should not be modified, so whoever calls string1() and gets the
	// returned string should not modify it:
// https://www.securecoding.cert.org/confluence/display/seccode/STR30-C.+Do+not+attempt+to+modify+string+literals
	// For more information, see:
	// http://stackoverflow.com/questions/9970295/life-time-of-string-literal-in-c
	//
	// It would be better to change this into "const char *str =
	// "Hello world";" and then return a "const *char" instead of a
	// "*char". This would help the programmer and compiler identify
	// the problem before you run it and see a crash.
	char *str = "Hello world";
	return str;
}

char *stringLocal(void)
{
	// Although this looks like a string literal, it is stored into an
	// array that is local in scope. Therefore, if we try to print
	// this string after returning from this function, it may print
	// garbage memory.
	char str[] = "Hello world";
	return str; // intentionally return a locally declared string!
}

int main(void)
{
	printf("%s\n", stringMalloc());
	printf("%s\n", stringLiteral());
	printf("%s\n", stringLocal());
	return 0;
}
