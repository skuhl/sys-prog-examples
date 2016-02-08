// Scott Kuhl
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


	// strlen() counts the number of non-null bytes. Therefore str2
	// and str3 should be the same length according to strlen():
	printf("strlen(str2)=%zu\n", strlen(str2));
	printf("strlen(str3)=%zu\n", strlen(str3)); // ERROR, could crash
	

	char twoNull[] = { 'h','i','\0','w','o','r','l','d','\0' };
	printf("%s\n", twoNull); // will print up to first null byte

	// Use fwrite() to write 9 bytes to stdout. Will print all bytes,
	// including null bytes (which probably won't show up in your
	// terminal.
	fwrite(twoNull, 9, 1, stdout);
	printf("\n");
	
	


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
