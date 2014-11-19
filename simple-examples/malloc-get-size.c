// Scott Kuhl
//
// There is no reliable way to determine how much space a malloc'd
// pointer refers to without keeping track of it in your program. This
// program demonstrates one way you can attempt to figure this out.
// Also see: http://stackoverflow.com/questions/1281686/determine-size-of-dynamically-allocated-memory-in-c
#define _GNU_SOURCE  // malloc_usable_size() is a GNU extension
#include <stdio.h>
#include <malloc.h>

int main(void)
{
	int mallocSize = 321;
	printf("Allocating %d bytes with malloc()\n", mallocSize);
	char *m = malloc(mallocSize);

	// sizeof() does not work with malloc as you might expect (see
	// sizeof.c). To get the amount of space that we have malloc()'d,
	// try using malloc_usable_size() on Linux.

	// The man page says:
	/*
	  The value returned by malloc_usable_size() may be greater than the
	  requested size of the allocation because of alignment and minimum
	  size constraints.  Although the excess bytes can be overwritten by
	  the application without ill effects, this is not good programming
	  practice: the number of excess bytes in an allocation depends on the
	  underlying implementation.

       The main use of this function is for debugging and introspection.
	*/
	size_t usableSize = malloc_usable_size(m);
	printf("Usable size: %zu\n", usableSize);

}
