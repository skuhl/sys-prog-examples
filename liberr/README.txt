USAGE:
LD_PRELOAD=/path/to/liberr.so programToRun arg1 arg2 ...
ALTERNATIVE USAGE:
./liberrRun programToRun arg1 arg2 ...

DESCRIPTION:
liberr demonstrates how to intercept function calls that a program makes. If liberr implements a function that you are calling, the following will occur:

 0) The program will call the function normally, but liberr will actually intercept the function call and instead call a function with the same name in liberr.

 1) liberr will print a message to stderr describing function that was called for every function call. This happens if the liberr_printInfo variable is set to 1 when liberr.so is compiled.

 2) liberr will call the "real" version of the function that you called using the same arguments you passed into the function.

 3) liberr will check the return value of the "real" function and print a message if an error occurred. liberr will also return the real return value back to your program---so using liberr shouldn't change the behavior of your program (other than printing out additional information to stderr).


OTHER SIMILAR PROGRAMS
The "strace" command on Linux will trace system calls and signals---but not necessarily any function the program calls.
