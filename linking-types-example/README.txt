=== Compiling ===

Run "make static" to build a program called "static" that demonstrates
how to build a static library. Note: Building this program will delete
the dynamic library file that the "shared" and "dynamic" examples use.

Run "make shared" to build a program called "shared" that demonstrates
how to build a shared library. Note: Building this program will delete
the static library file that the "static" example uses.

Run "make dynamic" to build a program called "dynamic" that
demonstrates how to build a dynamic library. Note: Building this
program will delete the static library file that the "static" example
uses.

=== Running ===

The statically linked version of the program will work like a normal program.

The shared and dynamically linked programs will likely NOT run. They
will fail because the OS does not typically look in the current
directory to look for libraries---it usually only looks in standard
locations such as "/usr/lib".

Environment variables are used to communicate to the OS where it
should look for libraries. The name of the environment variable
depends on your OS:

 - Linux:  LD_LIBRARY_PATH
 - Mac OS X: DYLD_LIBRARY_PATH

The remainder of these instructions assume that you are using Linux.

To make matters more complicated, the procedure to set these
environment variables depends on which shell you are using. In any
given shell, you can typically set an environment variable for a
one-time command OR you can set an environment variable for an entire
shell session (until you exit it!).

How do I know which shell I'm using? 

 - Run the "ps" command. It will show some of the processes your user
   is running. One of them should be your shell.

 - Run "echo $SHELL" at the command line. This will show you the
   contents of the SHELL environment variable which is typically set
   to the path to your shell.

The bash shell is often the default on any typical Linux
distribution. The tcsh shell is also often the default at Michigan
Tech.


** Bash shell **

You can set environment variables for a one-time command like this:

LD_LIBRARY_PATH=. ./dynamic
LD_LIBRARY_PATH=. ./shared

You can change the environment permamently for a terminal session (the
setting will go away when you exit) like this:

export LD_LIBRARY_PATH=.
./dynamic
./shared

** tcsh shell **

You can set environment variables for a one-time command like this
(this method should also work for other shells too!)

env LD_LIBRARY_PATH=. ./dynamic
env LD_LIBRARY_PATH=. ./shared

You can change the environment permamently for a terminal session (the
setting will go away when you exit) like this:

setenv LD_LIBRARY_PATH .
./dynamic
./shared


** fish shell **

To run a one-time command with an environment variable:
[ See instructions for tcsh shell ]

You can change the environment permamently for a terminal session (the
setting will go away when you exit) like this:
set -gx LD_LIBRARY_PATH .
