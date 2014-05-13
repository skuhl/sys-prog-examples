// Scott Kuhl
/* This file demonstrates some of the nuances and details of reading
 * binary files with fgetc(). You may find it easier to use fread().
 *
 * Run the program, read the comments, look at fgetc.temp using xxd.
 */


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#define FILENAME "fgetc.temp"

int main(void)
{

	// write some bytes to the file
	FILE *fp = fopen(FILENAME, "w");
	// 255 stored in a char is the same as -1 stored in a char---all bits are set.
	char list[] = { 'x', 255, -1, 'x', '\n', 'E', 'N', 'D' };
	printf("writing %lu bytes to %s; please view it with xxd.\n", sizeof(list), FILENAME);
	fwrite(list, sizeof(list), 1, fp);
	fclose(fp);

	struct stat s;
	stat(FILENAME, &s);
	printf("file size is: %u\n", (int) s.st_size);

	// fgetc() can return 257 different values. Values 0-255 are
	// regular ASCII characters. The 257th value is for when
	// end-of-file occurs. When end-of-file occurs, fgetc() returns an
	// integer -1 (the preprocessor defines EOF to be -1).


	// The following loop won't read the entire file. Since the return
	// value of fgetc() can be 0 through 255, there isn't a return
	// value that isn't already used that can be used to indicate EOF.
	printf("This loop won't read all bytes in the file:\n");
	fp = fopen(FILENAME, "r");
	char c;
	do
	{
		c = fgetc(fp); // MISTAKE! fgetc() documentation says it returns an int!
		printf("read byte: %c (decimal value is %d)\n", c, c);
	} while(c != EOF);
	if(feof(fp) == 0)
		printf("we exited the do-while loop because we thought we hit EOF, but feof() says we didn't.\n");

	fclose(fp);
	
	// This loop works.
	printf("This loop will read all bytes in the file:\n");
	fp = fopen(FILENAME, "r");
	int i;
	do
	{
		i = fgetc(fp);
		printf("read byte: %c (decimal value is %d)\n", (char)i, i);
	} while(i != EOF);
	if(feof(fp) == 0)
		printf("we exited the do-while loop because we thought we hit EOF, but feof() says we didn't.\n");

	fclose(fp);

	
	
	return 0;
}
