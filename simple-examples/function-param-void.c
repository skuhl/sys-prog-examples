// Scott Kuhl
//
// For more information, see:
// http://stackoverflow.com/questions/12225171/difference-between-int-main-and-int-mainvoid

#include <stdio.h>

/* Both func1 and func2 do not take any parameters. However, you will
 * receive different messages from the compiler when you try to call
 * them with a parameter! */

void func1()
{
	printf("func1()\n");
}

/* If your function doesn't take a parameter, it is best to write it
 * this way because it will result in a clearer compiler
 * warning/error. */
void func2(void)
{
	printf("func2()\n");
}


int main(void)
{
	func1(123); // GCC produce NO compiler warning!

	// Try uncommenting the following line:
	//func2(123); // GCC produces an error
}
