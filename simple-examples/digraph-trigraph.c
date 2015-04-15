// Scott Kuhl

#include <stdio.h>

int main(void)
{
	/* C will convert the following sequence of 3 characters into a
	   single character. These frequently aren't needed any more since
	   modern keyboards provide all of the keys needed to type source
	   code. For more information, see:
	   http://en.wikipedia.org/wiki/Digraphs_and_trigraphs#C

	   Trigraph   Replacement
	   ??=        #
	   ??/        \
	   ??'        ^
	   ??(        [
	   ??)        ]
	   ??!        |
	   ??<        {
	   ??>        }
	   ??-        ~

	   Digraph    Replacement
	   <:         [
	   :>         ]
	   <%         {
	   %>         }
	   %:         #
	*/

	char str??(10??) = "Hello";
	if(str[0] == 'H')
	??<
		printf("String begins with 'H'.\n");
	%>

	printf("Trigraph replacement happens inside of strings: ??=\n");
	printf("Digraph replacement does not: %:\n");

	// Is the next line executed????/
	printf("Here!");
	// The printf() line is not run because ??/ gets replaced to be \
	// which when used at the end of a comment allows a multiline
	// comment.


// /* starts a comment but here we insert a new line between the '/' and the '*'
/\
* This is a real comment. *\
/

// Same as previous example, but uses trigraphs
/??/
* This is also a real comment. *??/
/

}
