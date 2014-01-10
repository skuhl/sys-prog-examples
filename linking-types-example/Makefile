all: shared

CFLAGS=-Wall -g -std=c99


libfoo.a:
	gcc ${CFLAGS} -c one.c two.c
	ar cr libfoo.a one.o two.o

libfoo.so: one.c two.c
	gcc ${CFLAGS} -fPIC -c one.c two.c
	gcc -shared -o libfoo.so one.o two.o

shared: libfoo.so main.c
	rm -f libfoo.a  # force use of .so file
	gcc -o shared main.c  -L. -lfoo 

static: libfoo.a main.c
	rm -f libfoo.so  # force use of .a file
	gcc -o static main.c -L. -lfoo

dynamic: libfoo.so dlexample.c
	rm -f libfoo.a  # force use of .so file
	gcc ${CFLAGS} -o dynamic dlexample.c -ldl

clean:
	rm -f libfoo.a libfoo.so *.o static dynamic shared
