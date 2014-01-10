// Scott Kuhl
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	// Two literal strings can be concatenated if placed next to each
	// other.
	printf("String 1" "String 2\n");

	// Use f postfix character to tell compiler to treat a number as a
	// float.
	printf("sizeof(float) = %zu %zu\n", sizeof(float), sizeof(1.2f));

	// Decimal numbers are treated as doubles.
	printf("sizeof(double) = %zu %zu\n", sizeof(double), sizeof(1.2));

	// Use L postfix to indicate a long double
	printf("sizeof(long double) = %zu %zu\n", sizeof(long double), sizeof(1.2L));

	// integers are "int" by default
	printf("sizeof(int) = %zu %zu\n", sizeof(int), sizeof(1));

	// Use UL postfix to indicate an unsigned int.
	printf("sizeof(unsigned int) = %zu %zu\n", sizeof(unsigned int), sizeof(1U));

	// Use L postfix to indicate an long int
	printf("sizeof(long) = %zu %zu\n", sizeof(long), sizeof(1L));

	// Use L postfix to indicate an long int
	printf("sizeof(unsigned long) = %zu %zu\n", sizeof(unsigned long), sizeof(1UL));

	// Setting bits inside of a string:
	// 1 byte:  \nnn         n = octal digit
	// 1 byte:  \xnn         n = hex digit
	// 2 bytes: \unnnn       n = hex digit
	// 2 bytes: \Unnnnnnnn   n = hex digit
	char string[] = "hello\x21";
	printf("%s\n", string);

	int decimal = 10;
	int octal = 012;
	int hexadecimal = 0x0a;
	int binary = 0b1010; // gcc extension.
	printf("%d %d %d %d\n", decimal, octal, hexadecimal, binary);

	return 0;
}
