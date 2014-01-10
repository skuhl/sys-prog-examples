Run "make static" to build a program called "static" that demonstrates how to build a static library. Note: Building this program will delete the dynamic library file that the "shared" and "dynamic" examples use.

Run "make shared" to build a program called "shared" that demonstrates how to build a shared library. Note: Building this program will delete the static library file that the "static" example uses.

Run "make dynamic" to build a program called "dynamic" that demonstrates how to build a dynamic library. Note: Building this program will delete the static library file that the "static" example uses.


You will need to run the shared and dynamic executables using the following commands. Without setting LD_LIBRARY_PATH, the operating system will not realize that it will find the library in your current directory.

LD_LIBRARY_PATH=. ./dynamic
LD_LIBRARY_PATH=. ./shared
