// Scott Kuhl
#include <stdio.h>
#include <stdlib.h>

void print_array(const int a[], const int size)
{
	for(int i=0; i<size; i++)
		printf("%d ", a[i]);
	printf("\n");
}

int main(void)
{
	int a[3] = { 1, 2, 3 };
	int b[]  = { 3, 2, 1 }; // Length of B is determined from initializer

	// Arrays and pointers behave in similar, but not identical
	// ways. For example, arrays are like pointers that can't be
	// changed (but the data that they point at can be changed!). The
	// following lines are errors because they would change where the
	// array 'a' is pointing at.

	// a = b;                     // ERROR
	// a = { 3, 2, 1 };           // ERROR
	// a = (int []) { 3, 2, 1 };  // ERROR

	print_array(a, 3);
	print_array(b, 3);


	
	// However, pointers can be reassigned and can also act like arrays:
	int *aptr = (int []) { 1, 2, 3 }; /* This allocates space on the
	                                   * stack for the array. The
	                                   * memory that aptr is pointing
	                                   * at will be accessible only
	                                   * within the block of code that
	                                   * contains this line of
	                                   * code. */
	
	int *bptr = malloc(3 * sizeof(int)); /* The address returned by
	                                      * malloc should be free()'d
	                                      * eventually! The memory
	                                      * that bptr points at will
	                                      * be accessible until it is
	                                      * freed()'d. */
	bptr[0] = 3;
	bptr[1] = 2;
	bptr[2] = 1;
	print_array(aptr, 3);
	print_array(bptr, 3);
	free(bptr);

	
	/* Arrays may or may not be initialized to 0 */
	int noInit[3]; // CAN be initialized to ANYTHING! Depends on compiler.
	static int noInitStatic[3]; // static arrays are initialized to zero.
	print_array(noInit, 3);
	print_array(noInitStatic, 3);


	/* Fewer initializers than space. C99 spec says:
	   
	   If there are fewer initializers in a brace-enclosed list than
	   there are elements or members of an aggregate, or fewer
	   characters in a string literal used to initialize an array of
	   known size than there are elements in the array, the remainder
	   of the aggregate shall be initialized implicitly the same as
	   objects that have static storage duration.
	 */
	int big[32] = { 0 }; // guaranteed initialization to 0
	print_array(big, 32);
	
	/* Designated initializers */
	int desigA[6] = { [1] = 77, 88, [4] = 99 };
	// ... is equivalent to ...
	int desigB[6] = { 0, 77, 88, 0, 99, 0 };
	// Just as described above, omitted field members are implicitly
	// initialized the same as objects that have static storage
	// duration.
	print_array(desigA, 6);
	print_array(desigB, 6);
}
