/* Scott Kuhl

   getopt() is a POSIX function that makes it easy makes it easy to
   parse command line arguments.

   This program demonstrates how to handle *single* character
   arguments using getopt().

   You can handle arguments such as "--debug" or similar if
   you use getopt_long() instead of getopt().

   You should run all of the following an learn what they do if you
   really want to understand how getopt() works:
   
   ./getopt -a
   ./getopt -a -c
   ./getopt -a extraparam
   ./getopt extraparam -a
   ./getopt extraparam -a -c
   ./getopt -a -b
   ./getopt -ab
   ./getopt -ba
   ./getopt -f hello
   ./getopt -fhello
   ./getopt -afhello
   ./getopt -fahello
   ./getopt -o
   ./getopt -ohello
   ./getopt -o hello
   
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

void help_and_exit(char *executable)
{
	printf("Usage for %s\n", executable);
	printf(" -a                   Does something\n");
	printf(" -b                   Does something else\n");
	printf(" -f value OR -fvalue  Sets a value. The value is required\n");
	printf(" -o OR -ovalue        Sets a different value. The value is optional. '-o value' will not work\n"); // GNU extension, not POSIX.
	exit(EXIT_FAILURE);
}

int main(int argc, char* argv[])
{
	while(1)
	{
		/* Information about the 3rd parameter to getopt() below:
		   
		   If the first character is a colon, then getopt() returns
		   ':' instead of '?' to indicate a missing option argument.
		   
		   If ONE colon is after a character, than that option requires an
		   argument (i.e., "-f something" or "-fsomething").

		   If there are TWO colons after a character, you can
		   optionally include an argument (i.e., "-o" and
		   "-osomething" are both valid). This is a GNU Extension and
		   is not (not POSIX-compliant).
		   
		   So, ":af:" means that getopt() will return ":" if an
		   argument is required for a option but isn't
		   present. (Trigger this case by running "./getopt
		   -f"). Also, the '-a' option is accepted (which doesn't
		   accept an argument) and the '-f' option is accepted (which
		   requires an additional option after it).
		*/
		int c = getopt(argc, argv, ":abf:o::");
		if(c == -1) // no more option characters
			break;

		switch(c)
		{
			case 'a':
				printf("Using the -a option\n");
				break;
			case 'b':
				printf("Using the -b option\n");
				break;
			case 'f': // requires an argument after -f
				printf("f: %s\n", optarg); // print the argument after -f
				break;
			case 'o':
				printf("o: %s\n", optarg); // print the argument after -o
				break;
			case ':':
				printf("Missing argument to -%c\n", optopt);
				help_and_exit(argv[0]);
				break;
			case '?':
				printf("Used an argument unknown to getopt(): %c\n", optopt);
				help_and_exit(argv[0]);
				break;
			default:
				printf("Used an argument known to getopt() but not in our switch statement: %c\n", optopt);
				help_and_exit(argv[0]);
				break;
		}
	}

	/* IMPORTANT: getopt() will "permute the contents of argv while it
	   scans". Therefore, you shouldn't plan on using argv if you use
	   getopt(). The ONLY time where you can use argv is to process
	   any remaining arguments that getopt() didn't process. Those
	   arguments will always be moved to the end of argv by
	   getopt().

	   The code below will print any remaining arguments
	   (that don't begin with a '-' character).
	*/
	for(int i=optind; i<argc; i++) // optind is the index into argv that contains the first extra argument.
		printf("Parameters not handled by getopt(): argv[%d]=%s\n", i, argv[i]);
	
	printf("Program exited normally\n");
	return 0;
}
