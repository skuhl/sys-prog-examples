liberr.so: liberr.c
	gcc -Wall -Wextra -fPIC liberr.c -nostartfiles -shared -rdynamic -Wl,-soname,liberr.so -o liberr.so -ldl

.PHONY: clean
clean:
	rm -f liberr.so
