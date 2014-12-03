// Scott Kuhl
#include <stdio.h>

int main(void)
{
    /* Nested functions are not in the C standard. GCC supports them,
       however. Since not all compilers support nested functions, they
       should be avoided unless you are completely certain that your
       code will only compiled with a compiler that supports them.
    */
	void hello()
	{
		printf("Hello\n");
	}

	hello();
	printf("World\n");

}
