// Scott Kuhl
#include <stdio.h>
#include <stdlib.h>

int global; // global variables are initialized to 0

void func(void)
{
	int localFunc; // local variables are not initialized
	static int localFuncStatic; // static variables are always initialized.
	
	printf("localFunc=%d\n", localFunc); // intentionally use uninitialized variable
	printf("localMainStatic=%d\n", localFuncStatic);
}


int main(void)
{
	int localMain; // local variables are not initialized

	printf("global=%d\n", global);
	printf("localMain=%d\n", localMain); // intentionally use uninitialized variable
	func();
	return 0;
}
