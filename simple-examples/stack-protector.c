// Scott Kuhl
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// GCC includes a -fstack-protector-all option that puts a random
// value at a location near the edge of the stack that shouldn't be
// changed. When a function returns, the program will then check to
// ensure the canary value is still there. If it is changed, the
// program wrote data outside of the stack. On some machines, this GCC
// option may be enabled by default. On others, you may have to
// manually add it to your compilation options (i.e., in the
// makefile).

// For more information: http://wiki.osdev.org/GCC_Stack_Smashing_Protector

void stackExample(char *copyIntoBuf)
{
	char buf[5];
	strcpy(buf, copyIntoBuf);
}

int main ()
{
	stackExample("hi"); // OK, less than 5 bytes
	stackExample("This is longer than 5 bytes."); // WRONG!

	// If -fstack-protector-all is working correctly, the program will
	// exit with a message indicating that stack smashing occurred
	// during the second call to stackExample().

	return 0;
}
