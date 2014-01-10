// Scott Kuhl
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char *str = (char*) malloc(sizeof(char)*3);
	strncpy(str, "hi", 3);
	printf("%s\n", str);

	// Allocate more space:
	char *str2 = realloc(str, sizeof(char)*6);
	if(str2 == NULL)
	{
		// Since we passed a size into realloc() that is larger than
		// 0, str2 will be null only when an error occurred. If an
		// error occurs, str is untouched and we must free it.
		free(str);
		printf("realloc failed.\n");
		exit(EXIT_FAILURE);
	}
	// If realloc is successful, we don't have to worry about
	// free()'ing str---but we should free() str2 when we are done
	// with it. str2 will either be the same memory address as str1,
	// or it will be a different adddress. If it is a different
	// address, realloc() will free(str) for us.
	
	// Note: str may (or may not) now point to a new location.
	strncpy(str2, "hello", 6);
	printf("%s\n", str2);
	free(str2);
	return EXIT_SUCCESS;
}
