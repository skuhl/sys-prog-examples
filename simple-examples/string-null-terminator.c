// Scott Kuhl
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	
	char *str1 = "Hello"; // null terminated
	char str2[] = { 'w', 'o', 'r', 'l', 'd', '\0' }; // null terminated
	char str3[] = { 'w', 'o', 'r', 'l', 'd' }; // lacks null terminator

	printf("%s\n", str1); // OK, str1 is null terminated
	printf("%s\n", str2); // OK, str2 is null terminated


	/* Since str3 does not have a terminating null byte, it will just
	 * print bytes until it finds one. This could cause us to try to
	 * access bytes that we are not supposed to access. If the byte
	 * after str3 happens to be a null byte, than this program may run
	 * as expected. However, if compiled on a different machine, with
	 * different optimization settings, that could change.
	 *
	 * Even if this program doesn't crash or print garbage, Valgrind
	 * should be able to catch this mistake.
	 */
	printf("%s\n", str3); // ERROR, could crash


	/* Unless otherwise stated, you should assume that all functions
	   that operate strings require null-terminated strings.

	   For example:
	    - strcmp() compares two null terminated strings
	    
	    - memcmp() compares a specified number of bytes (i.e., it
          does not require a null terminator to be present---but you
          need to tell it how many bytes to compare)
	*/

	
	return 0;
}
