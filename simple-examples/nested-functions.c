// Scott Kuhl
#include <stdio.h>

int main(void)
{
#ifdef __linux__
	
    /* Nested functions are not in the C standard. GCC supports them,
       however. Since not all compilers support nested functions, they
       should be avoided unless you are completely certain that your
       code will only compiled with a compiler that supports them.

       For more information, see:
       https://gcc.gnu.org/onlinedocs/gcc/Nested-Functions.html
    */
	void hello()
	{
		printf("Hello\n");
	}

	hello();
	printf("World\n");
	return 0;


#else

	/* Disabling on OSX for now since there is no reliable way to make
	 * this example compile. It should work with the version of gcc
	 * used by homebrew */
	printf("Nested functions aren't supported by OSX's /usr/bin/gcc (which uses the LLVM backend)\n");
	return 0;
	
#endif
}
