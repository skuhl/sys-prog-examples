/* Scott Kuhl

   getopt() makes it easy to parse command line arguments. This
   program demonstrates how to handle single character arguments using
   getopt().

   In this example, we only show how to process single character
   arguments. You can handle arguments such as "--debug" or similar if
   you use getopt_long() instead of getopt().
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

int main(int argc, char* argv[])
{
	while(1)
	{
		/* Information about the 3rd parameter to getopt() below:
		   
		   If the first character is a colon, then getopt() returns
		   ':' instead of '?' to indicate a missing option argument.
		   
		   If one  colon is after a character, than that option requires an
		   argument (i.e., "-f something"). If there are two colons
		   after a character, you can optionally include an argument
		   (i.e., "-f" and "-f something" are both valid).
		   
		   So, ":af:" means that getopt() will return ":" if an
		   argument is required for a option but isn't
		   present. (Trigger this case by running "./getopt
		   -f"). Also, the '-a' option is accepted (which doesn't
		   accept an argument) and the '-f' option is accepted (which
		   requires an additional option after it).
		*/
		int c = getopt(argc, argv, ":af:");
		if(c == -1) // no more option characters
			break;

		switch(c)
		{
			case 'a':
				printf("Using the -a option\n");
				break;
			case 'f': // requires an argument after -f
				printf("f: %s\n", optarg); // print the argument after -f
				break;
			case ':':
				printf("Missing argument to -%c\n", optopt);
				// fall through
			default:
				printf("Usage for %s\n", argv[0]);
				printf(" -a         Does something\n");
				printf(" -f value   Does something else\n");
				
				exit(EXIT_FAILURE);
		}
	}

	/* If the program takes arguments that are not processed by
	 * getopt, for example: "./getopt -a inputFile outputFile", then
	 * you can process the remaining arguments here: */
	for(int i=optind; i<argc; i++)
		printf("Not handled by getopt(): argc[%d]=%s\n", i, argv[i]);
	
	printf("Program exited normally\n");
}
