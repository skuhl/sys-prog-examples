// Scott Kuhl
#include <stdio.h>
#include <stdlib.h>

int main (void)
{
	printf("Press Ctrl+C to exit.\n");
	while(1)
	{
		printf("Type in something:\n");
		char buf[1024];
		fgets(buf, 1024, stdin);
		printf("You typed:\n");
		// You shouldn't allow a user to type in a formatting string!
		printf(buf);
		// Correct:
		// printf("%s", buf);
		// Correct:
		// puts(buf);

		printf("\n");
		printf("What happens if you type '%%d' or '%%s' or '%%s%%s%%s%%s'?\n");
	}

   return(0);
}
