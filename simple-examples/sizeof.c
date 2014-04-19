// Scott Kuhl
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <limits.h> // for int/long/short min/max values
#include <float.h>  // for float/double min/max values
#include <stdint.h> // for int32_t, etc types

int main(void)
{
	int i = 0;
	printf("sizeof(i):     %zu\n", sizeof(i));
	printf("sizeof(int):   %zu\n", sizeof(int));

	char array[42];
	printf("sizeof(array): %zu\n", sizeof(array));

	char *m = (char*) malloc(sizeof(char)*10);
	printf("sizeof(m):     %zu (actually size of char*)\n", sizeof(m));
	free(m);
	printf("sizeof(char*): %zu\n", sizeof(char*));

	printf("\nSize of common types on this computer:\n");
	printf("For more info: https://en.wikipedia.org/wiki/C_data_types\n");
	printf("sizeof(char):        %zu (always 1)\n", sizeof(char));
	printf("sizeof(float):       %zu (IEEE 754 single precision float - 4)\n", sizeof(float)); // FLT_MIN to FLT_MAX
	printf("sizeof(double):      %zu (IEEE 754 double precision float - 8)\n", sizeof(double)); // DBL_MIN to DBL_MAX
	printf("sizeof(long double): %zu (unspecified, at least a double)\n", sizeof(long double)); // LDBL_MIN to LDBL_MAX
	printf("sizeof(int):         %zu (at least 2; in practice, often 4)\n", sizeof(int));  // INT_MIN to INT_MAX
	printf("sizeof(long):        %zu (at least 4)\n", sizeof(long)); // LONG_MIN to LONG_MAX
	printf("sizeof(long long):   %zu (at least 8)\n", sizeof(long long)); // LLONG_MIN to LLONG_MAX
	printf("sizeof(short):       %zu (at least 2)\n", sizeof(short)); // SHRT_MIN to SHRT_MAX
	printf("sizeof(void*):       %zu (typically 4 on 32 bit machines, 8 on 64 bit machines)\n", sizeof(void*));
	// uintptr_t can be used to cast a pointer into an unsigned
	// integer. It can be converted back into a void* to get the
	// original pointer once again. This means that it is probably the
	// same size as void*, but not necessarily. See:
	// http://stackoverflow.com/a/1846648
	printf("sizeof(uintptr_t):   %zu (may be same size as a pointer)\n", sizeof(uintptr_t)); 

	printf("\n");
	printf("sizeof(pid_t):   %zu\n", sizeof(pid_t));
	printf("sizeof(clock_t): %zu\n", sizeof(clock_t));
	printf("sizeof(size_t):  %zu\n", sizeof(size_t));
	printf("sizeof(ssize_t): %zu\n", sizeof(ssize_t));
	printf("sizeof(time_t):  %zu\n", sizeof(time_t));
	printf("\nData types with guaranteed sizes (there are more types than these!):\n");
	printf("sizeof(int8_t):  %zu (should be 1)\n", sizeof(int8_t));
	printf("sizeof(int16_t): %zu (should be 2)\n", sizeof(int16_t));
	printf("sizeof(int32_t): %zu (should be 4)\n", sizeof(int32_t));
	printf("sizeof(int64_t): %zu (should be 8)\n", sizeof(int64_t));

	// Defined in limit.h
	//
	// By default, "char" may or may not be signed. Use "signed char"
	// or "unsigned char" to be explicitly clear. GCC will treat plain
	// "char" as signed unless you compile with -funsigned-char to
	// tell GCC that you want "char" treated as unsigned. Recompiling
	// this with different settings will cause CHAR_MIN and CHAR_MAX
	// to print different values.
	printf("number of bits in a char: %d\n", CHAR_BIT);
	printf("minimum value for a signed char: %d\n", SCHAR_MIN);
	printf("maximum value for a signed char: %d\n", SCHAR_MAX);
	printf("maximum value for an unsigned char: %d\n", (int) UCHAR_MAX ); 
	printf("minimum value for a char: %d\n", (int) CHAR_MIN );
	printf("maximum value for a char: %d\n", (int) CHAR_MAX );
	printf("maximum multibyte length of a character accross locales: %d\n", MB_LEN_MAX );
	printf("minimum value for a short: %d\n", SHRT_MIN );
	printf("maximum value for a short: %d\n", SHRT_MAX );
	printf("maximum value for an unsigned short: %d\n", USHRT_MAX);
	printf("minimum value for an int: %d\n", INT_MIN);
	printf("maximum value for an int: %d\n", INT_MAX);
	printf("maximum value for an unsigned int: %d\n", UINT_MAX );
	printf("minimum value for a long: %ld\n", LONG_MIN );
	printf("maximum value for a long: %ld\n", LONG_MAX );
	printf("maximum value for an unsigned long: %lu\n", ULONG_MAX);
	printf("minimum value for a long long: %lld\n", LLONG_MIN);
	printf("maximum value for a long long: %lld\n", LLONG_MAX);
	printf("maximum value for an unsigned long long: %llu\n", ULLONG_MAX);

	printf("\n");
	printf("For floats, minimum values are the smallest value greater than 0\n");
	printf("minimum value of a float: %f\n", FLT_MIN);
	printf("maximum value of a float: %f\n", FLT_MAX);
	printf("minimum value of a double: %lf\n", DBL_MIN);
	printf("maximum value of a double: %lf\n", DBL_MAX);
	printf("minimum value of a long double: %Lf\n", LDBL_MIN);
	printf("maximum value of a long double: %Lf\n", LDBL_MAX);

	return 0;
}
