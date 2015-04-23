// Scott Kuhl
#include <stdio.h>

int main(void)
{
	// This is a comment. This is supported in C99 and newer.

	/* This is also a comment. This is the only type of
	   comment allowed in ANSI C  */


	// Comments like this should be avoided. This is \
	a \
	multiline \
	comment

	// Other things that are allowed and should be avoided.

	// A comment with the // split across lines (you can also do this
	// with /* and */

	/\
/ comment


	// Unrelated to comments, but you can insert newlines in the
	// middle of almost anything:
	print\
f("hello world\n");

}
