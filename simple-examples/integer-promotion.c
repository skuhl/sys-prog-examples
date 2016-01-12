// Scott Kuhl

/* Types such as char and short are promoted to int when operations
 * are performed on them. */


#include <stdio.h>
int main(void)
{
	// Maximum value for an unsigned char is 255
	unsigned char hundred = 100;

	// In the line below, hundred * hundred is promoted to an int,
	// stored in an unsigned char.
	//
	// In the same way that you can do "int x = 123.3" without a cast
	// and get no warning, the same happens below.
	//
	// TIP: Add the -Wconversion compiler flag to catch cases where
	// things are being implicitly cast in a way that may alter the
	// value.
	unsigned char product = hundred * hundred;
	
	// But multiplying two unsigned chars together results in an int.
	printf("%d\n", product); // Prints (100*100)%256 = 16
	printf("%d\n", hundred * hundred); // prints 10000

	/* NOTE: The promotion even occurs on things that you might not
	 * normally expect it. For example, when you do a bitshift, or a
	 * bitwise not. The promotion happens prior to the bitshift
	 * operator being applied. */
}
