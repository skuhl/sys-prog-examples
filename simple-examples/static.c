// Scott Kuhl
#include <stdio.h>

/* Static functions and static global variables are only visible in
 * the file that it is declared in. Static variables inside of a
 * function have a different meaning and is described below */

void foo()
{
	int x = 0;
	static int staticx = 0; // initialized once; keeps value between invocations of foo().
	x++;
	staticx++;
	printf("x=%d\n", x);
	printf("staticx=%d\n", staticx);
}

int main(void)
{
	for(int i=0; i<10; i++)
		foo();
}
