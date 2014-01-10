// Scott Kuhl
// Requires libreadline to be installed. Compile with -lreadline
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
	while(1)
	{
		// readline allows a user to edit their input with arrow keys,
		// backspace, etc. Other ways of reading from the terminal
		// (fgets()) usually do not provide such capabilities.
		char *line = readline("User-friendly prompt> ");
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
