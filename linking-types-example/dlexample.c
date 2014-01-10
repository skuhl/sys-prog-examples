#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>

int main(void)
{

	// path could be absolute path---relative paths trigger normal
	// library searching.
    void *handler = dlopen("libfoo.so", RTLD_LAZY);
    if (!handler)
    {
        fprintf(stderr,"%s\n", dlerror());
        exit(EXIT_FAILURE);
    }
    // get access to a function in library
    // int = return value of the function
    // *fn = pointer to a function named fn
    // () = comma separated list of arguments to function. Example: (int *, char c)
    int (*one) () = dlsym(handler,"one");
    char *error;
    if ((error = dlerror()) != NULL) /* checking error through dlerror() */
    {
        fprintf(stderr,"%s\n", error);
        exit(EXIT_FAILURE);
    }

    int (*two) () = dlsym(handler,"two");
    if ((error = dlerror()) != NULL) /* checking error through dlerror() */
    {
        fprintf(stderr,"%s\n", error);
        exit(EXIT_FAILURE);
    }

    
    // call the function
    // Older way to call a pointer to a function: (*one)();
    // The more familiar way:
    one();
    two();

    // close the handler
    dlclose(handler);
    return EXIT_SUCCESS;
}
