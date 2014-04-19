// Scott Kuhl
#include <stdio.h>
#include <stddef.h>

int main(void)
{
	typedef struct {
		int a;
		char b;
		int c;
	} triplet;

	// Compiler will typically add padding to align the elements in a
	// struct to word boundaries. For more information, see:
	// https://en.wikipedia.org/wiki/Data_structure_alignment
	printf("sizeof(triplet) = %zu\n", sizeof(triplet));
	printf("Sum of each element size = %zu\n",
	       2*sizeof(int)+sizeof(char));

	triplet x;
	ptrdiff_t aLoc = (ptrdiff_t) &(x.a);
	ptrdiff_t bLoc = (ptrdiff_t) &(x.b);
	ptrdiff_t cLoc = (ptrdiff_t) &(x.c);

	printf("Bytes between start of 'a' and start of 'b': %td\n", bLoc-aLoc);
	printf("Bytes between start of 'b' and start of 'c': %td\n", cLoc-bLoc);

	// Some compilers provide an option to use packed
	// structures. However, support depends on compiler and isn't
	// guaranteed to exist.

#pragma pack(push)  /* push current alignment to stack */
#pragma pack(1)     /* set alignment to 1 byte boundary */
	typedef struct {
		int a;
		char b;
		int c;
	} packed_triplet;
#pragma pack(pop)   /* restore original alignment from stack */
	
	printf("Packed struct: %zu\n", sizeof(packed_triplet));

	return 0;
}
