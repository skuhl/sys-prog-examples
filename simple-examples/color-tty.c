// Scott Kuhl

// Demonstrates how to print color to a terminal using ANSI color
// codes. This may not work on all terminals. Most programs will us
// isatty() to determine if it is communicating to a terminal and then
// also check the TERM environment variable to see if the terminal
// itself supports color. This program doesn't do either of these
// extra checks.

#include <stdio.h>
#define NRM  "\x1B[0m"

#define BLK  "\x1B[30m"
#define RED  "\x1B[31m"
#define GRN  "\x1B[32m"
#define YEL  "\x1B[33m"
#define BLU  "\x1B[34m"
#define MAG  "\x1B[35m"
#define CYN  "\x1B[36m"
#define WHT  "\x1B[37m"

#define BLK_BG  "\x1B[40m"
#define RED_BG  "\x1B[41m"
#define GRN_BG  "\x1B[42m"
#define YEL_BG  "\x1B[43m"
#define BLU_BG  "\x1B[44m"
#define MAG_BG  "\x1B[45m"
#define CYN_BG  "\x1B[46m"
#define WHT_BG  "\x1B[47m"

#define BOLD  "\x1B[1m"
#define ULINE "\x1B[4m"


void printColors(void)
{
	printf("normal\n");
	printf(BLK "black\n");
	printf(RED "red\n");
	printf(GRN "green\n");
	printf(YEL "yellow\n");
	printf(BLU "blue\n");
	printf(MAG "magenta\n");
	printf(CYN "cyan\n");
	printf(WHT "white" NRM "\n"); // also, reset back to normal
}

int main(void)
{
	printColors();
	
	printf(BOLD);
	printf("\nBold:\n");
	printColors();

	printf(ULINE);
	printf("\nUnderline:\n");
	printColors();

	
	printf(BOLD);
	printf(RED_BG);
	printf("\nRed background + bold:\n");
	printColors();

	printf(BLU_BG);
	printf("\nBlue background + normal:\n");
	printColors();

	printf("You can also " BOLD RED_BG "highlight" NRM " individual words.\n");

	return 0;
}
