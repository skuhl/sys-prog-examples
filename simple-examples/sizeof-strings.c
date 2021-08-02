// Scott Kuhl
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char array[11] = "hello world"; // 11 chars, no null terminator
	// Will print 11 since sizeof() on an array returns the size of
	// the whole array in bytes. 1 char is always 1 byte.
	printf("sizeof(array) = %lu\n", sizeof(array)); 
	
	char *ptrToStringLiteral = "hello world"; // 11 chars
	// sizeof() on a pointer will return the size of the pointer. Typically, this is 8 bytes on most machines.
	printf("sizeof(ptrToStringLiteral) = %lu\n", sizeof(ptrToStringLiteral));

	char *mallocedString = malloc(12); // 11 chars + 1 null terminaotr
	sprintf(mallocedString, "hello world"); // copy our message into malloc'd space
	// this is same as the previous example---still prints the size of the pointer.
	printf("sizeof(mallocedString) = %lu\n", sizeof(mallocedString));
	free(mallocedString);

	// this will print the size of the string + 1 for the null terminator (!!!).
	printf("sizeof(\"hello world\") = %lu\n", sizeof("hello world"));


	// TAKEAWAY MESSAGE: When possible, use null terminated strings
	// and strlen() to calculate string lengths. strlen() counts the
	// number of characters before the null terminator (without
	// counting the null terminator).

	// WHY?
	// If you have an array of chars, you can still use strlen() as
	// long as you are certain that there is a null terminator at the
	// end of the string in the array: Just call strlen(array). If you
	// wish to start counting from a place in the string after the
	// first byte, use something like strlen(&(array[3])).
	//
	// If you have an array which is not null terminated, you could
	// use sizeof(). However, remember that sizeof() tells you the
	// overall size of the array in bytes----not the size of the
	// string (which might not fill the whole array).
	//
	// For more about the intricacies of sizeof(), see sizeof.c
	
	return 0;
}
