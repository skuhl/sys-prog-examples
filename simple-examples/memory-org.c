// Scott Kuhl
//
// More info about organization of memory on Linux: http://lwn.net/Articles/91829/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <malloc.h>
#include <stdint.h>
#include <dlfcn.h>
int globalVar = 10;


void printAddress(char *str, void *ptr)
{
	printf("%16p or %20lu - %s\n", ptr, (uintptr_t) ptr, str);
}

void addStack(void)
{
	// create an array that won't be optimized out by compiler
	int i = 5;

	// Calling this function should add 
	printAddress("&i inside function (stack)", &i);
}


int main(int argc, char *argv[])
{
	(void)argc; // we don't use argc, causes compiler not to warn us about it.
	
	// The output of this program may change over a series of runs due to:
	// https://en.wikipedia.org/wiki/Address_space_layout_randomization
	int i = 10;
	char *str1 = "hello world"; // string literals are stored in the text region of memory, not on the heap.
	char str2[] = "hello world"; // stored on stack

	// highest addresses contain memory used by the OS:
	printAddress("getenv", getenv("PATH"));
	printAddress("argv", argv);

	// The stack grows downward (the first address below is higher than the second address)
	printAddress("&i inside main (stack)", &i);
	addStack();
	printAddress("str2 inside main (stack)", str2);

	// String literals are stored in the .text section of memory (at the bottom of the stack)
	printAddress("str1 inside main (text)", str1);

	/* malloc() usually uses the heap to allocate memory. It does so by calling sbrk() to move the "program break" which is the top of the heap. Moving the "program break" to a higher value will give your process more memory. malloc() does this for you. If change the program break with sbrk(), you might break other functions that actually use malloc(). */
	printAddress("sbrk (heap)", sbrk(0));
	void *m = malloc(1024);
	printAddress("m (heap)", m);
	// NOTE: malloc() may use a few bytes for its own bookkeeping, 
	printAddress("sbrk after malloc (heap)", sbrk(0));
	free(m);
	// free()'ing memory doesn't necessarily move sbrk back down.
	printAddress("sbrk after free (heap)", sbrk(0));
	// instead, memory might be reused for future malloc()'s:
	m = malloc(10);
	void *m2 = malloc(100);
	printAddress("m (heap)", m);
	printAddress("m2 (heap)", m2);
	printAddress("sbrk after 2 more mallocs (heap)", sbrk(0));
	free(m);
	free(m2);

	/* malloc() uses mmap() when large areas of space are requested. */
	m = malloc(1024*128*50); // typically mmap is used for allocations larger than 128k
	printAddress("m (that may have been allocated with mmap) (mmap)", m);
	printAddress("sbrk after malloc (that may use mmap) (heap)", sbrk(0));
	free(m);

	printAddress("globalVar (text)", &globalVar);
	
	printAddress("printAddress (text)", printAddress);

	 // since we dynamically link to printf, its isn't defined until
	 // the linker links this program to libc at runtime. The address
	 // that is printed out is the address of the PLT for
	 // printf---which will then in-turn call printf().
	printAddress("printf PLT (text)", printf);

	return EXIT_SUCCESS;
}
