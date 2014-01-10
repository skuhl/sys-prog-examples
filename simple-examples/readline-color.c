// Scott Kuhl
// Requires libreadline to be installed. Compile with -lreadline
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

// We begin with \001 and end with \002 to avoid confusing readline. If we don't use the \001 and \002, line wrapping won't work:
// http://stackoverflow.com/questions/9468435
#define KNRM  "\001\x1B[0m\002"
#define KRED  "\001\x1B[31m\002"


int main(void)
{
	while(1)
	{
		// readline allows a user to edit their input with arrow keys,
		// backspace, etc. Other ways of reading from the terminal
		// (fgets()) usually do not provide such capabilities.
		char *line = readline(KRED "User-friendly prompt> " KNRM);
		if(!line)
			printf("Error reading user input.\n");
		else
		{
			printf("User entered: %s\n", line);
			if(strcmp(line, "exit") == 0 ||
			   strcmp(line, "quit") == 0)
			{
				free(line);
				exit(EXIT_SUCCESS);
			}
			else
				free(line);
		}
	}
}
