// Scott Kuhl
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>   // Needed for int8_t, etc.
#include <inttypes.h> // Needed to use PRI* with printf()

int main(void)
{
	uint8_t a  =  1;
	int8_t b   = -1;
	uint16_t c =  2;
	int16_t d  = -2;
	uint32_t e =  3;
	int32_t f  = -3;
	uint64_t g =  4; // not required by C99 standard
	int64_t h  = -4; // not required by C99 standard
	// Another type: uintptr_t is an unsigned integer that is the same size as a pointer on the machine. 

	// Normal formatting strings like %d are mapped to a particular
	// type (such as int that might be some particular number of
	// bytes).

	// In this example, the variables have a fixed number of bytes,
	// and those might map to different types of actual C types (int,
	// char, short, etc.). The PRI* formatting strings will create a
	// formatting string appropriate for a type of that size.
	printf("a=%"PRIu8" b=%"PRId8"\n", a, b);
	printf("c=%"PRIu16" d=%"PRId16"\n", c, d);

	printf("e=%"PRIu32" f=%"PRId32"\n", e, f);
	printf("g=%"PRIu64" h=%"PRId64"\n", g, h);

	// These things are actually just strings!
	printf("strings: %s %s %s %s %s %s %s %s\n", PRIu8, PRId8, PRIu16, PRId16, PRIu32, PRId32, PRIu64, PRId64);

	printf("Octal:\n");
	printf("a=%"PRIo8" b=%"PRIo8"\n", a, b);
	printf("c=%"PRIo16" d=%"PRIo16"\n", c, d);
	printf("e=%"PRIo32" f=%"PRIo32"\n", e, f);
	printf("g=%"PRIo64" h=%"PRIo64"\n", g, h);

	printf("Hex:\n");
	printf("a=%"PRIx8" b=%"PRIx8"\n", a, b);
	printf("c=%"PRIx16" d=%"PRIx16"\n", c, d);
	printf("e=%"PRIx32" f=%"PRIx32"\n", e, f);
	printf("g=%"PRIx64" h=%"PRIx64"\n", g, h);
}
