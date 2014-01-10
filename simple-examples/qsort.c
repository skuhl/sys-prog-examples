// Scott Kuhl
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int compare(const void *aIn, const void *bIn)
{
	/* Everything passed into this function is a void pointer. We need
	 * to cast it into something else if we want to use it. First, we
	 * cast aIn fro a void* to a float*, then we dereference it and
	 * store the value into a. */
	float a = *((float*)aIn);
	float b = *((float*)bIn);

	/* It may be tempting to do something like a-b (which would return
	 * <0 if 'a' is smaller; returns >0 if b is smaller; and returns 0
	 * if a==b). You may encounter wrapping problems. What if both 'a'
	 * and 'b' are near the smallest possible values? */
	if(a < b)
		return -1;
	else if(a > b)
		return 1;
	return 0;
}

int main(void)
{
	float f[] = { 1.2, 3, 2, 1 };
	int n=4; // number of items

	printf("Before sorting:\n");
	for(int i=0; i<n; i++)
		printf("%f\n", f[i]);
	
	qsort(f, n, sizeof(float), compare);
	
	printf("After sorting:\n");
	for(int i=0; i<n; i++)
		printf("%f\n", f[i]);

	exit(EXIT_SUCCESS);
}
