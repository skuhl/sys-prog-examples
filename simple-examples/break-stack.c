// Scott Kuhl
//
// Your stack has a limit to what it grow to. This program tries to
// allocate a huge amount of space on the stack, causing the program
// to crash.
//
// Run "limit" or "limits" from the command-line to see the maximum
// stack size allowed.
//
// You can avoid this problem by allocating large amounts of space on
// the heap (with malloc()) or using Making the large array a global
// (or static) variable may also work---since they aren't allocated on
// the stack.

#include <stdio.h>

int main(void)
{
	int size = 1024*1024*1024; // 1 gig
	char array[size];  // doesn't work
//	static char array[1024*1024*1024]; // works
	
	// use the array to try to prevent the compiler from optimizing it out.
	for(int i=0; i<size; i++) 
		array[i] = i % 256;
	printf("Finished!\n");
	return 0;
}
