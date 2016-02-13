Run "make static" to build a program called "static" that demonstrates how to build a static library. Note: Building this program will delete the dynamic library file that the "shared" and "dynamic" examples use.

Run "make shared" to build a program called "shared" that demonstrates how to build a shared library. Note: Building this program will delete the static library file that the "static" example uses.

Run "make dynamic" to build a program called "dynamic" that demonstrates how to build a dynamic library. Note: Building this program will delete the static library file that the "static" example uses.


You will need to run the shared and dynamic executables using the following commands. Without setting the LD_LIBRARY_PATH environment variable (on Linux), the operating system will not realize that it will find the library in your current directory. The way that you set environment variables depend on the shell that you are using. Typing "ps" on the command line should show you all of the processes that have been started in that particular terminal session. It should show you your shell. Most systems default to the bash shell.

** Bash shell **

You can set environment variables for a one-time command like this:
LD_LIBRARY_PATH=. ./dynamic
LD_LIBRARY_PATH=. ./shared

You can change the environment permamently for a terminal session (the setting will go away when you exit) like this:
export LD_LIBRARY_PATH=.
./dynamic
./shared

** tcsh shell **

You can set environment variables for a one-time command like this (this method should also work for other shells too!)
env LD_LIBRARY_PATH=. ./dynamic
env LD_LIBRARY_PATH=. ./shared

You can change the environment permamently for a terminal session (the setting will go away when you exit) like this:
setenv LD_LIBRARY_PATH .
./dynamic
./shared


** fish shell **

To run a one-time command with an environment variable:
[ See instructions for tcsh shell ]

You can change the environment permamently for a terminal session (the setting will go away when you exit) like this:
set -gx LD_LIBRARY_PATH .


