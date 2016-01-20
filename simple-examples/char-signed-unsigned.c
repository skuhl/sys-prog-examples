// Scott Kuhl

/*
  "char" is always 1 byte in C. There are three versions of "char" in C:

  Signed
  Unsigned
  Neither (in which case, your system will pick either signed or unsigned).

  For more definitive information, start by looking at section
  5.2.4.2.1 in the C99 standard.

  When you are treating characters as actual ASCII characters, the
  difference don't matter much. However, when you are using char's to
  store numbers, then it does start to matter!

  Note that 'char' is the only type in C that has this
  distinction. For example, 'int' is always the same as 'signed int'.
*/

#include <limits.h>
#include <stdio.h>

int main(void)
{
	printf("minimum value for a signed char: %d\n", SCHAR_MIN);
	printf("maximum value for a signed char: %d\n", SCHAR_MAX);
	printf("maximum value for an unsigned char: %d\n", (int) UCHAR_MAX ); 
	printf("minimum value for a char: %d\n", (int) CHAR_MIN );
	printf("maximum value for a char: %d\n", (int) CHAR_MAX );

	if(SCHAR_MIN == CHAR_MIN && SCHAR_MAX == CHAR_MAX)
		printf("The 'char' type seems to be the same as 'signed char' on this machine.\n");
	else if(CHAR_MIN == 0 && UCHAR_MAX == CHAR_MAX)
		printf("The 'char' type seems to be the same as 'unsigned char' on this machine.\n");
	else
		printf("Huh?\n");

	// 'H' is 72 in decimal according to ASCII. In this case, the
	// contents of all three variables below will all be the same.
	signed char signedH = 'H';
	unsigned char unsignedH = 'H';
	char plainH = 'H';
	printf("SignedH: %c %d\n", signedH, signedH);
	printf("UnsignedH: %c %d\n", unsignedH, unsignedH);
	printf("PlainH: %c %d\n", plainH, plainH);

	// No ASCII character has a value greater than 128. Just assign
	// the char a number instead.
	signed char signedTwoHund = 200;     // overflow! Compiler error or warning?
	unsigned char unsignedTwoHund = 200; 
	char plainTwoHund = 200;             // Possible overflow. Compiler error or warning?

	// Any variables above that have overflowed probably wrapped around
	printf("SignedTwoHund: %c %d\n", signedTwoHund, signedTwoHund);
	printf("UnsignedTwoHund: %c %d\n", unsignedTwoHund, unsignedTwoHund);
	printf("PlainTwoHund: %c %d\n", plainTwoHund, plainTwoHund);
}
