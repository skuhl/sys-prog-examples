sys-prog-examples
=================

This repository contains a collection of simple C programs that demonstrate different aspects of programming on Linux. They were originally developed by Scott Kuhl to complement CS3411 Systems Programming at Michigan Technological University. Some of the example programs lack complete error checking (i.e., they don't check the return values for some functions to look for errors). Some of the example programs are intended for you to run multiple times and try editing. If you are looking for information about how to use a particular function or concept, you might want to try using "grep" to look for it instead of looking solely at the filenames. Looking at the man pages for the functions used in the programs will also be helpful.

All programs should compile and run on modern Linux machines. Compile all of them by typing "make" and clean up all binaries by typing "make clean". Some of these programs may have the same names as programs in /usr/bin or similar, so you need to run them as "./programName" to ensure that you are using the right program.

Downloading
=============

To download the latest version of this repository in a ZIP file, use this link:   https://github.com/skuhl/sys-prog-examples/archive/master.zip

To download this repository onto a Linux machine that has git installed, try:

    git clone https://github.com/skuhl/sys-prog-examples.git
	cd sys-prog-examples

To ensure that your copy of the repository is up-to-date, run the following when you are in the sys-prog-examples directory:

    git pull

If you want to ensure that your copy of the repository exactly matches the latest version of the this repository, run the following when you are in the sys-prog-examples directory (this will delete any local files you added to the directory!):

	git fetch --all
	git reset --hard origin/master
