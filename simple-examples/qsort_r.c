// Scott Kuhl
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// If you want to use a single compare function that changes behavior
// based on another argument, you can use qsort_r() and add an
// additional parameter to your comparison function (a void* variable
// called "thunk").
//
// Also, if your compare function changes a global variable and you
// could have multiple threads running qsort and touching that same
// global variable at the same time---there could be problems!
// qsort_r() would allow you to use one compare function, but to tell
// each thread what data it should be working with (besides the actual
// data that is getting sorted).
static int compare(const void *aIn, const void *bIn, void *thunkIn)
{
	float a   = *((float*)aIn);
	float b   = *((float*)bIn);
	int thunk = *((int*)thunkIn);

	if(thunk == 0)
	{
		if(a < b)
			return -1;
		else if(a > b)
			return 1;
		return 0;
	}
	else
	{
		if(a > b)
			return -1;
		else if(a < b)
			return 1;
		return 0;
	}
}

int main(void)
{
	float f[] = { 1.2, 3, 2, 1 };
	int n=4; // number of items

	printf("Before sorting:\n");
	for(int i=0; i<n; i++)
		printf("%f\n", f[i]);

	// In this example, thunk is an integer. It could be anything (a
	// struct, an array, etc).
	int thunk = 0; // NOTE: Try setting thunk to 1
	qsort_r(f, n, sizeof(float), compare, &thunk);
	
	printf("After sorting:\n");
	for(int i=0; i<n; i++)
		printf("%f\n", f[i]);

	exit(EXIT_SUCCESS);
}
