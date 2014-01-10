// Scott Kuhl
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	// See stdint.c for more examples.
	int sint = -42;
	printf("int: %d %i\n", sint, sint); // %d and %i are the same thing
	printf("int: %o\n", sint); // octal
	printf("int: %x\n", sint); // hex(lowercase)
	printf("int: %X\n", sint); // hex(uppercase)
	printf("\n");

	int one = 1;
	printf("int: %d\n", one);
	printf("int: |%5d|\n", one); // use 5 characters to print value, | there to help you count the space it uses.
	printf("int: |%-5d|\n", one); // left justify (it right justifies by default)
	printf("int: |%05d|\n", one); // pad with zeros
	printf("int: %+d\n", one); // always include sign
	printf("int: %x\n", sint); // hex(lowercase)
	printf("int: %X\n", sint); // hex(uppercase)
	printf("\n");
	
	unsigned uint = 42;
	printf("unsigned int: %u\n", uint);
	printf("\n");

	long l = -111; // a long is larger than an int
	printf("long: %ld\n", l); // as a signed value
	printf("long: %lu\n", l); // as an unsigned value
	printf("long: %lo\n", l); // octal
	printf("long: %lx\n", l); // hex(lowercase)
	printf("long: %lX\n", l); // hex(uppercase)
	printf("\n");

	long long ll = -222; // a long is larger than an int
	printf("long: %lld\n", ll); // as a signed value
	printf("long: %llu\n", ll); // as an unsigned value
	printf("long: %llo\n", ll); // octal
	printf("long: %llx\n", ll); // hex(lowercase)
	printf("long: %llX\n", ll); // hex(uppercase)
	printf("\n");
	
	char ch='Z';
	printf("char: %c\n", ch);
	printf("char: %d\n", ch); // decimal
	printf("char: %o\n", ch); // octal
	printf("char: %x\n", ch); // hex(lowercase letters)
	printf("char: %X\n", ch); // hex(uppercase letters)
	printf("\n");

	float f=1.239;
	printf("float: %f\n", f);
	printf("float: |%5.2f|\n", f); // (use 20 characters total for
								   // number, 2 after decimal point, |
								   // characters are there so you can
								   // easily count how many characters
								   // it uses up. It performs rounding!
	printf("float: |%05.2f|\n", f); // same as above, pad with 0s
	printf("\n");

	double d=9.8764;
	printf("double: %lf\n", d);
	printf("double: |%5.2lf|\n", d);
	printf("double: |%05.2lf|\n", d);
	printf("\n");




	printf("A percent sign: %%\n");
}
