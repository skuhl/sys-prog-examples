SOURCE=$(wildcard *.c)
HEADER=$(wildcard *.h)
EXEC=$(SOURCE:.c=)

# Some of the programs use pthreads, readline and dynamic linking
# (dl). We will compile all programs against the libraries---because
# that is easier than writing a makefile that singles out only the
# specific programs that use the libraries.
LIBS=-lrt -lpthread -lreadline -ldl -lm

# -Wpedantic with -std=c99 will warn if programs use extensions that
# aren't supported by C99. Using -std=c99 alone won't cause warnings
# if you use some GNU extensions (such as nested functions).
CFLAGS=-Wall -Wextra -Wpedantic -std=c99 -D_FORTIFY_SOURCE=2
DEBUG=-g
OPT=-O2

CC=gcc
CPPCHECK=/usr/bin/cppcheck

all: ${EXEC}

.SECONDEXPANSION:
${EXEC}: $$(addsuffix .c, $$@) Makefile
	${CC} ${CFLAGS} ${DEBUG} ${OPT} -o $@ $@.c ${LIBS}

.PHONY: clean
# a.out - some people might manually compile the program this way.
# file.txt - some programs create this file.
# gmon.out - created by programs compiled with -pg (see gprof-demo)
# *.temp - Some programs might create a file named something.temp.
# core - created by core-dump.c
# We delete .o files even though we don't create them. Some people manually compiling their programs may create them!
clean:
	rm -f a.out file.txt gmon.out *.temp ${EXEC} ${EXEC:=.o} core *~
