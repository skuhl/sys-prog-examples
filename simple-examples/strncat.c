// Scott Kuhl
//
// How to concatenate two strings with strncat(). Carefully shows how
// to calculate n correctly.
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define DEST_SIZE 12
int main(void)
{
	char *dest = (char*) malloc(sizeof(char)*DEST_SIZE);
	sprintf(dest, "hello"); // initialize dest

	printf("dest capacity is %d\n", DEST_SIZE);
	printf("strlen(dest) = %lu\n", strlen(dest));
	printf("bytes used in dest (including null byte) = %lu\n", strlen(dest)+1);
	printf("bytes unused in dest = %lu\n", DEST_SIZE-strlen(dest)-1);

	// man page for strncat(char *dest, char *src, size_t n) says the
	// size of dest must be at least strlen(dest)+n+1. In other words:
	//              DEST_SIZE   >= strlen(dest) + n + 1
	// DEST_SIZE-strlen(dest)   >= n + 1
	// DEST_SIZE-strlen(dest)-1 >= n
	
	// So, we must say n = DEST_SIZE-strlen(dest)-1 or we must use an
	// even smaller value for n.

	int n = DEST_SIZE-strlen(dest)-1;
	printf("we are using n = %zu\n", DEST_SIZE-strlen(dest)-1);
	strncat(dest, " world", n);
	printf("%s\n", dest);
	
	// Try again with an n that is smaller than what it needs to
	// be. No problems occur---except that we don't end up copying all
	// of the src string onto the end of the dest string.
	sprintf(dest, "hello"); // initialize dest
	strncat(dest, " world", DEST_SIZE-strlen(dest)-2);
	// We won't overrun dest if it isn't large enough.
	printf("%s (destination not large enough)\n", dest);

	// Change #if 1 to #if 0 to disable the examples below.
#if 1
	// Try again with an n that is too large for the capacity of
	// dest. Might cause a crash, warning, etc. If no crash or
	// warning, try using valgrind to see the problem.
	sprintf(dest, "hello"); // initialize dest
	strncat(dest, " worldX", DEST_SIZE-strlen(dest)); // WRONG
	printf("%s (WRONG - malloc)\n", dest);
#endif

#if 1
	// Same as previous example, but on the stack (valgrind might not
	// catch this problem!).
	char destStack[DEST_SIZE];
	sprintf(destStack, "hello");
	strncat(destStack, " worldX", DEST_SIZE-strlen(destStack)); // WRONG
	printf("%s (WRONG - stack)\n", destStack);
#endif
	
	free(dest);
	return 0;
}
