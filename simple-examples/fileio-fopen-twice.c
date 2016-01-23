// Scott Kuhl

/* This example demonstrates using one file stream to write to a file
 * and another file stream to read from the file.
 *
 * NOTE: The function calls in this program lack error checking.
 */
#include <stdio.h>

#define FILENAME "fileio-fopen-twice.temp"

int main(void)
{
	// Write a message to a file.
	FILE *fout = fopen(FILENAME, "w");
	fprintf(fout, "Hello world.");

	// Create another file stream to read the same file.
	FILE *fin = fopen(FILENAME, "r");

	// Show the file streams are different
	printf("fout=%p\n", (void*)fout);
	printf("fin =%p\n", (void*)fin);

	// Get the filesize from our second file stream
	fseek(fin, 0L, SEEK_END);
	long length = ftell(fin);
	printf("File has length %ld\n", length); // could be zero, changes not flushed out.

	// Flush what we wrote.
	fflush(fout);

	// Check file size again.
	fseek(fin, 0L, SEEK_END);
	length = ftell(fin);
	printf("File has length %ld\n", length); 

	// Add more data to the file
	fprintf(fout, "  This is a test.");
	fflush(fout);

	// Check the file size again; show that it can change
	fseek(fin, 0L, SEEK_END);
	length = ftell(fin);
	printf("File has length %ld\n", length);

	// cleanup
	fclose(fin);
	fclose(fout);
	remove(FILENAME);
}
