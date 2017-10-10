// Scott Kuhl
#include <stdio.h>
#include <string.h> // memcpy()
int arrayA[3];
int arrayB[3];

void resetArrays()
{
	printf("Resetting arrays to the original values.\n");
	arrayA[0] = 1;
	arrayA[1] = 2;
	arrayA[2] = 3;

	arrayB[0] = 9;
	arrayB[1] = 8;
	arrayB[2] = 7;
}

void printArrays()
{
	printf("arrayA = %d %d %d\n", arrayA[0], arrayA[1], arrayA[2]);
	printf("arrayB = %d %d %d\n", arrayB[0], arrayB[1], arrayB[2]);
}

int main(void)
{
	resetArrays();
	printf("Arrays initially set to:\n");
	printArrays();

	printf("Copying B into A with a loop.\n");
	for(int i=0; i<3; i++)
		arrayA[i] = arrayB[i];
	printArrays();


	// memcpy() effectively copies your data the same way a loop
	// does. Note that memcpy() assumes the two sections of memory do
	// not overlap. Use memmove() instead if they might overlap.
	printf("Copy B into A with memcpy()");
	resetArrays();
	memcpy(arrayA, arrayB, sizeof(int)*3);
	printArrays();


#if 0    // Set to 1 to see compilation error/warning.
	resetArrays();
	printf("Make arrayA point to arrayB.\n");
	arrayA = arrayB;
	printArrays();
	/* Note: You can assign pointers to each other in C. Even though
	 * arrayA and arrayB (when used without the square braces after
	 * them) are like pointers, you can't change what they point to
	 * after they have been created. For more info, see:
	 * https://stackoverflow.com/questions/12676402/why-cant-i-treat-an-array-like-a-pointer-in-c
	 */
#endif

	return 0;
}
