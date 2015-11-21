// Scott Kuhl

/* Stack space is typically limited and you won't receive any warnings
 * when you exhaust stack space. Common ways to overflow the stack
 * include too deep of recursion or simply allocating an array on the
 * stack that is too big (as we do in this example). You can set and
 * view your current stack limits using the "ulimit" command on Linux.
 *
 * Takeaway messages:
 *   1) Don't allocate large arrays in functions (i.e., on the stack).
 *   2) Use malloc() to allocate large arrays.
 **/

#include <stdio.h>
#include <stdlib.h>

#ifdef __linux__
/* getrlimit() */
#include <sys/time.h>
#include <sys/resource.h>
#endif

int f(unsigned long bytes)
{
	char buf[bytes]; // allocate space on the stack

	/* "Use" the array so allocation isn't optimized away by compiler;
	   also prevent compiler warnings about unused variables. */
	for(unsigned long i=0; i<bytes; i++)
		buf[i] = rand() % 256; // fill with random numbers
	int sum=0;
	for(unsigned long i=0; i<bytes; i++)
		sum += buf[i];
	return sum;
}

int main(void)
{
#ifdef __linux__
	/** What are the current stack size limits? */
	struct rlimit limit;
	if(getrlimit(RLIMIT_STACK, &limit) == 0) // if successful
	{
		printf("Stack limit (soft) = %ld\n", limit.rlim_cur);
		printf("Stack limit (hard) = %ld\n", limit.rlim_max);
	}
#endif

	unsigned long currentSize=1;
	while(currentSize > 0)
	{
		printf("Allocating %lu bytes on stack\n", currentSize);
		f(currentSize);
		
		currentSize = currentSize<<1; /* double the size; if we shift
		                                 our bit off the end,
		                                 currentSize will be zero. */
	}

	printf("Apparently we didn't crash...\n");
}
