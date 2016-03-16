// Scott Kuhl

// Demonstrates how to print color to a terminal using ANSI color
// codes. This may not work on all terminals. Most programs will us
// isatty() to determine if it is communicating to a terminal and then
// also check the TERM environment variable to see if the terminal
// itself supports color. This program doesn't do either of these
// extra checks.

#include <stdio.h>

/* The \x at the beginning of each of these strings is a hexadecimal
   literal. Therefore, \x1B is 00011011 in binary. If you consult an
   ASCII table, you will see that this is the the "ESC" or "Escape"
   character---which is a special non-printable character.

   The 'ESC' followed by the '[' character is called CSI or "Control
   Sequence Introducer".

   Next, The ASCII number (one or two digits) indicates the color.

   Finally, the 'm' ends the sequence.

   Special note: You can combine multiple formats in one separated by
   semicolons: \x1B[32;43m should produce green text on a yellow
   background.
*/
   
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

	// In C, you can concatenate literal strings by just putting them
	// next to each other. No commas or '+' symbols needed. This only
	// works for string literals, not character arrays.
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

	printf("Another \x1B[32;43mexample\n" NRM);

	return 0;
}
