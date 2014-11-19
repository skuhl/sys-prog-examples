// Scott Kuhl
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
	// See stdint.c for more examples.
	int sint = -42;
	printf("int: %%d=%d %%i=%i\n", sint, sint); // %d and %i are the same thing
	printf("int: %%o=%o\n", sint); // octal
	printf("int: %%x=%x\n", sint); // hex(lowercase)
	printf("int: %%X=%X\n", sint); // hex(uppercase)
	printf("\n");

	int one = 1;
	printf("int: %%d=%d\n", one);
	printf("int: |%%5d|=|%5d|\n", one); // use 5 characters to print value, | there to help you count the space it uses.
	printf("int: |%%-5d|=|%-5d|\n", one); // left justify (it right justifies by default)
	printf("int: |%%05d|=|%05d|\n", one); // pad with zeros
	printf("int: %%+d=%+d\n", one); // always include sign
	printf("int: %%x=%x\n", sint); // hex(lowercase)
	printf("int: %%X=%X\n", sint); // hex(uppercase)
	printf("\n");
	
	unsigned uint = 42;
	printf("unsigned int: %%u=%u\n", uint);
	printf("\n");

	long l = -111; // a long is larger than an int
	printf("long: %%ld=%ld\n", l); // as a signed value
	printf("long: %%lu=%lu\n", l); // as an unsigned value
	printf("long: %%lo=%lo\n", l); // octal
	printf("long: %%lx=%lx\n", l); // hex(lowercase)
	printf("long: %%lX=%lX\n", l); // hex(uppercase)
	printf("\n");

	long long ll = -222; // a long is larger than an int
	printf("long: %%lld=%lld\n", ll); // as a signed value
	printf("long: %%llu=%llu\n", ll); // as an unsigned value
	printf("long: %%llo=%llo\n", ll); // octal
	printf("long: %%llx=%llx\n", ll); // hex(lowercase)
	printf("long: %%llX=%llX\n", ll); // hex(uppercase)
	printf("\n");
	
	char ch='Z';
	printf("char: %%c=%c\n", ch);
	printf("char: %%d=%d\n", ch); // decimal
	printf("char: %%o=%o\n", ch); // octal
	printf("char: %%x=%x\n", ch); // hex(lowercase letters)
	printf("char: %%X=%X\n", ch); // hex(uppercase letters)
	printf("\n");

	float f=1.23987654f;
	printf("float: %%f=%f\n", f);
	printf("float: %%+f=%+f\n", f);
	printf("float: |%%5.2f|=|%5.2f|\n", f); // (use 5 characters total for
								   // number, 2 after decimal point, |
								   // characters are there so you can
								   // easily count how many characters
								   // it uses up. It performs rounding!
	printf("float: |%%05.2f|=|%05.2f|\n", f); // same as above, pad with 0s
	printf("float: %%f=%f %%F=%F\n", INFINITY, INFINITY); // capitalization
	printf("float: %%e=%e\n", f); // sci. notation, lowercase e
	printf("float: %%E=%E\n", f); // sci. notation, capital E
	printf("float: %%g=%g\n", f); // %e or %f, whichever is shorter, trailing zeros removed
	printf("float: %%G=%G\n", f); // %E or %F, whichever is shorter, trailing zeros removed
	
	printf("float: %%a=%a\n", f); // hex sci notation, lowercase e
	printf("float: %%A=%A\n", f); // hex sci notation, lowercase e
	
	printf("\n");

	
	
	double d=9.87654321;
	// All floats are promoted to doubles when %f (and related)
	// formatting strings are used with printf(). Therefore, you can
	// use %f to print both doubles and floats.
	// See: http://stackoverflow.com/questions/4264127
	//
	// One potential point of confusion: sscanf() handles
	// floats/doubles differently (%f=float, %lf=double, %Lf=long
	// double).
	printf("double: %%f=%f\n", d);
	printf("double: %%+f=%+f\n", d);
	printf("double: |%%5.2f|=|%5.2f|\n", d);
	printf("double: |%%05.2f|=|%05.2f|\n", d);
	printf("double: %%f=%f %%F=%F\n", INFINITY, INFINITY); // capitalization
	printf("double: %%e=%e\n", d); // sci. notation, lowercase e
	printf("double: %%E=%E\n", d); // sci. notation, capital E
	printf("double: %%g=%g\n", d); // %e or %f, whichever is shorter, trailing zeros removed
	printf("double: %%G=%G\n", d); // %E or %F, whichever is shorter, trailing zeros removed

	printf("double: %%a=%a\n", d); // hex sci notation, lowercase e
	printf("double: %%A=%A\n", d); // hex sci notation, lowercase e

	printf("\n");


	long double ld=9.87654321;
	printf("long double: %%Lf=%Lf\n", ld);
	printf("long double: %%+Lf=%+Lf\n", ld);
	printf("long double: |%%5.2Lf|=|%5.2Lf|\n", ld);
	printf("long double: |%%05.2Lf|=|%05.2Lf|\n", ld);
	printf("long double: %%Le=%Le\n", ld); // sci. notation, lowercase e
	printf("long double: %%LE=%LE\n", ld); // sci. notation, capital E
	printf("long double: %%Lg=%Lg\n", ld); // %e or %f, whichever is shorter, trailing zeros removed
	printf("long double: %%LG=%LG\n", ld); // %E or %F, whichever is shorter, trailing zeros removed

	printf("long double: %%La=%La\n", ld); // hex sci notation, lowercase e
	printf("long double: %%LA=%LA\n", ld); // hex sci notation, lowercase e

	printf("\n");

	printf("A percent sign: %%\n");
}
