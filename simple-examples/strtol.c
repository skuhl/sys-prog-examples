// Scott Kuhl

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>


void convertHexToDec(const char *hex)
{
	errno = 0; // strtol can set errno, but we need to make sure it is
			   // reset in case something else set it to a different
			   // value.
	long int decimal = strtol(hex, NULL, 16);
	printf("hexadecimal value %s is %ld in decimal\n", hex, decimal);
	if(errno == ERANGE)
	{
		if(decimal == LONG_MIN)
			printf("   Underflow occurred on conversion immediately above.\n");
		else if(decimal == LONG_MAX)
			printf("   Overflow occurred on conversion immediately above.\n");
	}
	else if(errno != 0)
	{
		printf("   Some other kind of error occurred immediately above.\n");
	}


	// Alternative to the way we called strtol() above: If you want to
	// know if strtol() encountered any invalid characters, call
	// strtol() this way:
	char *invalidChar;
	decimal = strtol(hex, &invalidChar, 16);
	if(*invalidChar)
		printf("   First invalid character was %c\n", *invalidChar);
}


int main (void)
{
	convertHexToDec("f");
	convertHexToDec("-f"); // negative signs are ok
	convertHexToDec("    -f"); // whitespace before is OK.
	convertHexToDec("deadbeef"); // https://en.wikipedia.org/wiki/Hexspeak
	convertHexToDec("0xdeadbeef"); // strtol can handle 0x if base=16
	convertHexToDec("0x7ffffffffffffffe"); // near overflow
	convertHexToDec("0x7fffffffffffffff"); // LONG_MAX on many machines
	convertHexToDec("0x8000000000000000"); // Actual overflow
	convertHexToDec("1xyz2"); // ignore characters when a non-hex character is encountered
	convertHexToDec("xyz2"); // same as zero
	convertHexToDec(""); // same as zero
	
	return 0;
}
