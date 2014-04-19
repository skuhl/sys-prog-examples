// Scott Kuhl

#include <stdio.h>
#include <stdbool.h>

int main(void)
{
	// C99 provides a boolean type:
	bool b = false;
	printf("boolean is set to: %d\n", b);
	b = !b;
	printf("boolean is set to: %d\n", b);

	printf("bytes in a boolean: %zu\n", sizeof(bool));
	// Why is a bool take up a byte?  The C standard just says that a
	// bool is big enough to contain a 0 and a 1. The smallest
	// addressable object in C is a char (1 byte).
	// See: http://stackoverflow.com/a/10630231/474549

	// true is usually typedef'd to a 0 or 1 (i.e., an int literal).
	printf("bytes of boolean value true: %zu\n", sizeof(true));

	return 0;
}
	
