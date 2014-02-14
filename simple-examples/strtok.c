#define _GNU_SOURCE
#include <string.h>
#include <stdio.h>

int main(void)
{
	char str[] = "Hello world.";
	char *token = strtok(str, " ");
	while(token != NULL)
	{
		printf("%s\n", token);
		token = strtok(NULL, " ");
	}

	printf("\n");
	printf("Note that the original string is changed by strtok:\n");
	printf("%s\n", str);

	printf("If you want to parse multiple strings concurrently with strtok(), use strtok_r()\n");
	char str1[] = "Foo bar";
	char str2[] = "Michigan Tech";

	// These variables are used by strtok_r() so it doesn't confuse
	// which string you are asking it to tokenize.
	char *saveptr1;
	char *saveptr2;
	char *tok1 = strtok_r(str1, " ", &saveptr1);
	while(tok1 != NULL)
	{
		// The first time through this loop, we will print "Michigan"
		// and then "Tech" and then print the first token in str1.
	   
		// The second time through this loop, only "Michigan" will be
		// printed out because str2 is changed by strtok_r() the first
		// time through the loop.
		char *tok2 = strtok_r(str2, " ", &saveptr2);
		while(tok2 != NULL)
		{
			printf("%s\n", tok2);
			tok2 = strtok_r(NULL, " ", &saveptr2);
		}
		printf("%s\n", tok1);
		tok1 = strtok_r(NULL, " ", &saveptr1);
	}

	return 0;
}
