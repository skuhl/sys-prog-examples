// Scott Kuhl
#include <stdio.h>
#include <stdint.h>

int main(void)
{
	// A union allows us to access the same data as if it were
	// different types.
	typedef union {
		uint32_t a;
		uint8_t b[4];
		float f;
	} quad;

	quad q;
	// Although we are writing this hexadecimal value in big-endian
	// order (most-significant bytes first), the compiler/computer
	// will store it in little endian order.
	q.a = 0x01020304;

	// We will see that the bytes have been swapped in order when we
	// print each byte:
	printf("%d %d %d %d\n", q.b[0], q.b[1], q.b[2], q.b[3]);

	// The same data may represent different numbers when accessed as
	// if it were a different type.
	q.a = 987654321;
	printf("%f\n", q.f);

	return 0;
}
