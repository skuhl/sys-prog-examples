// Scott Kuhl
#include <stdio.h>
#include <stdlib.h>

// size_t is an unsigned integer that has at least 16 bits. It may be
// larger than an int.
void mallocExample(size_t bytes)
{
	// allocate space using malloc(). It returns a void* which can be
	// casted into other types.
	printf("Allocating %zu bytes of memory with malloc()...\n", bytes);

	char* buffer = (char*) malloc(bytes);
	if(buffer == NULL)
	{
		fprintf(stderr, "malloc() failed.\n");
		exit(EXIT_FAILURE);
	}
	// Use the space allocated stored in buffer here. malloc() doesn't
	// guarantee that it will zero out the space it allocates. Its
	// behavior may depend on your compiler, compiler options, and/or
	// your operating system.
	printf("Counting non-null bytes...\n");
	int nonZeroBytes = 0;
	for(size_t i=0; i<bytes; i++)
		if(buffer[i] != 0)
			nonZeroBytes++;
	printf("%d bytes contained something other than zero.\n", nonZeroBytes);

	// Always use free() whenever you allocate space with
	// malloc(). Pay attention if data structures returned by
	// functions should be free'd or not. Valgrind can help you
	// identify places where you forgot to use free().
	printf("Freeing the allocated space...\n");
	free(buffer);

	/* Calling free() on something that has already been free'd
	   produces undefined behavior and may cause your program to
	   crash.
	*/
	// free(buffer); 
}

void callocExample(size_t bytes)
{
	printf("Allocating %zu bytes of memory with calloc()...\n", bytes);

	char* buffer = (char*) calloc(1, bytes);
	if(buffer == NULL)
	{
		fprintf(stderr, "calloc() failed.\n");
		exit(EXIT_FAILURE);
	}
	printf("Counting non-null bytes...\n");
	int nonZeroBytes = 0;
	for(size_t i=0; i<bytes; i++)
		if(buffer[i] != 0)
			nonZeroBytes++;
	// There should be 0 non-zero bytes when calloc() is used.
	printf("%d bytes contained something other than zero.\n", nonZeroBytes);

	printf("Freeing the allocated space...\n");
	free(buffer);
}


int main(void)
{
	mallocExample(1024*1024*1024);       // 1 gigabyte
	printf("\n");
	callocExample(1024*1024*1024);       // 1 gigabyte
	printf("\n");
	mallocExample(1024*1024*1024*1024L); // 1 terabyte
}
