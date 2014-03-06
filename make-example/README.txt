This folder demonstrates how you can use gcc and Make to automatically
generate dependency rules so that you don't have to code up a complex
Makefile that lists all of the dependencies of all of your files. The
makefile also demonstrates how you might deal with source files that
are in different directories.

This makefile will generate a folder named "tmp" in your current
folder. This "tmp" folder contains intermediate .o files and .d
files. It can be safely deleted at any time.
