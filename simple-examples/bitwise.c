// Scott Kuhl
#include <stdio.h>

int main(void)
{
	/*
	  char is always a byte in C. However, it may be signed, unsigned
	  or neither (i.e., unspecified). See char-signed-unsigned.c
	*/
	unsigned char a = 0x33; // 00110011 in binary;
	unsigned char b = 0x0F; // 00001111 in binary;

	// Values that we would expect
	unsigned char AandB = 0x03;
	unsigned char AorB  = 0x3F;
	unsigned char AxorB = 0x3C;
	unsigned char notA  = 0xCC;
	unsigned char notB  = 0xF0;
	if((unsigned char) (a & b) != AandB) printf("AND Fail!\n");
	if((unsigned char) (a | b) != AorB) printf("OR Fail!\n");
	if((unsigned char) (a ^ b) != AxorB) printf("XOR Fail!\n");
	if((unsigned char) (~a) != notA) printf("NOT A Fail!\n");
	if((unsigned char) (~b) != notB) printf("NOT B Fail!\n");

	/* Why are the casts above necessary? C will cast integer types
	 * that are smaller than a char to an integer. Without the cast,
	 * some compilers will sometimes complain about comparison between
	 * different types. See integer-promotion.c */


	/* This...      --> can be written like this:
	   a = a & b    -->  a &= b
	   a = a | b    -->  a |= b
	   a = a ^ b    -->  a ^= b
	*/

	// Use << to shift bits to the left. After the bits are shifted,
	// any blank bits are set to 0.
	unsigned char allOn = 0xFF;
	if( (unsigned char) (allOn << 1) != 0xFE ) printf("<< Fail!");
	if( (unsigned char) (allOn >> 4) != 0x0F ) printf("<< Fail!");


	// You can shift and assign at the same time:
	unsigned char tmp = 0xFF;
	tmp <<= 1;    // stores 0xFE in tmp


	// WARNING: Shifting by a negative amount is often allowed, but is
	// not defined by the C standard. Therefore, you should not do it!
	tmp = tmp << -1;

	// Effectively the same as above, but might not produce a compiler
	// warning. Regardless of if there is a warning, bitshifting by a negative number is undefined.
	// https://www.securecoding.cert.org/confluence/display/c/INT34-C.+Do+not+shift+an+expression+by+a+negative+number+of+bits+or+by+greater+than+or+equal+to+the+number+of+bits+that+exist+in+the+operand
	int outsmartCompiler = -1;
	tmp = tmp << outsmartCompiler;


	// WARNING: Shifting by an amount that is equal to or larger than
	// the precision of the type is undefined.
	int intA = 123;
	intA = intA << 32; // undefined because int is 32 bits
	tmp = tmp << 8;    // OK! because tmp is promoted to an int before the bitshift occurs. Then, it is converted back into a char.
	

	// WARNING: Bitwise operators do not work on floats or doubles.

	
	/* Bitshifts on signed integers may behave differently depending
	   on implementation. For example, when the variable type is
	   signed and when the most significant bit is 1. In this case,
	   when you shift the bits to the right, the new bits will be 1
	   (according to the GCC compiler) or 0 (according to the
	   Microsoft C compiler).

	   The C11 standard explains that bitshifts are
	   implementation-defined and have undefined aspects for signed
	   types.
	   https://www.securecoding.cert.org/confluence/display/c/INT13-C.+Use+bitwise+operators+only+on+unsigned+operands
	*/
	signed int allOnSigned = -1;
	printf("Bitshift right on a signed type keeps the most left bit...\n");
	if( (allOnSigned >> 1) == -1 )
		printf("...set to one.\n");
	else if( (allOnSigned >> 1) == 0x7F )
		printf("...set to zero.\n");
	else
		printf("huh?\n");
}
