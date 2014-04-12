// Scott Kuhl
//
// Demonstrate how to do a linear search (with lfind()) and binary
// search (with bsearch()) on a sorted array.

#include <search.h> // for lfind()
#include <stdlib.h> // for lsearch()
#include <unistd.h>
#include <stdio.h>

int comp(const void *lookfor, const void *v)
{
	int key     = *((int*) lookfor);
	int current = *((int*) v);
	if(key < current)
		return -1;
	if(key > current)
		return 1;
	return 0; // match
}

int main(void)
{
	
	int data[] = {   1,   2,   5,  10,  23,
	                45,  50,  70, 100, 203,
	               400, 500, 654, 799, 999 };
	size_t dataSize = 15;
	int lookFor = 203; // should be found at index 9
	// int lookFor = 666; // not found

	// Linear search:
	// void* found = lfind(&lookFor, data, &dataSize, sizeof(int), comp);
	// Binary search:
	void* found = bsearch(&lookFor, data, dataSize, sizeof(int), comp);

	if(found == NULL)
		printf("Didn't find value.\n");
	else
	{
		int *foundInt = (int*)found;
		// Use pointer arithmetic to calculate index:
		printf("Found at index %lu\n", foundInt-data);
	}

}
