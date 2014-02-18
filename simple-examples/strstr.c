// Scott Kuhl
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main (void)
{
	// https://en.wikipedia.org/wiki/The_quick_brown_fox_jumps_over_the_lazy_dog
	char haystack[] = "the quick brown fox jumps over the lazy dog";
	printf("%s\n", haystack);

	char *found = strstr(haystack, "fox");
	if(found)
	{
		// found is a pointer to the same string as haystack is.
		printf("%s\n", found);
		found[0]='P';
		found[1]='I';
		found[2]='G';
	}
	else
		printf("No match was found\n");

	printf("%s\n", haystack);

	return 0;
}
