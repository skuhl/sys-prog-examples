// Scott Kuhl
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

int main(void)
{
	typedef struct {
		unsigned short a : 1;
		unsigned short b : 1;
		unsigned short c : 1;
		unsigned short d : 4;
	} field;

	// There is only 1 bit allocated for 'a' in the bitfield.
	field f;
	f.a = 0;
	printf("%d\n", f.a);
	f.a = f.a+1;
	printf("%d\n", f.a);
	f.a = f.a+1; // wraparound.
	printf("%d\n", f.a);

	printf("\n");
	// There are 4 bits allocated for 'd' in the bitfield.
	f.d = 1;
	f.d = f.d+1;
	printf("%d\n", f.d);

	// The compiler can use padding. See struct-padding.c
	printf("size of field: %zu bytes\n", sizeof(field));

	// The compiler can put the bits bitfield in any order! Don't
	// write a bitfield to disk and assume another computer/compiler
	// will be able to read it.
	// For example, see: http://stackoverflow.com/a/4547887/474549
	
	return 0;
}
