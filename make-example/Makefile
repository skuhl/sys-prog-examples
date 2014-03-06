# name of executable
NAME    = test

# compiler to use
CC = gcc

# include directories
INCLDIR = -I/usr/include
# directories containing libraries (i.e., "-L/usr/lib")
LIBDIR  =
# libraries to link to
LIBS    = -lm

# Our source code files
SRC     = file1.c file2.c
# Our object files (addprefix handles the fact that the .c files in
# SRC are compiled into .o files in the "tmp" subfolder)
OBJ     = $(addprefix tmp/,$(SRC:.c=.o)) subdir/tmp/subfile.o

# Compiler options
OPT = -g -Wall

# Compilation flags
CFLAGS = ${OPT} ${INCLDIR}
# Linker flags
LDFLAGS = ${LIBDIR} ${LIBS}

# Describes how to link/create the binary.
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

# Describes how to create the subfile.o file by running "make" in a
# subdirectory.
subdir/tmp/subfile.o:
	make -C subdir

# Here, we ask the compiler to inspect our .c files and create a .d
# file that we can use in a makefile. As a result, the compiler will
# figure out what files your .c files depend on.
tmp/%.d: %.c
	@mkdir -p tmp
	@echo "Creating/recreating dependency file: $(@)"
	@set -e; $(CC) -MM $(CFLAGS) $< \
	| sed 's/\($*\)\.o[ :]*/tmp\/\1.o $* : /g' > $@; \
	[ -s $@ ] ||  rm -f $@

# Here is the command that want to use to create our C files.
tmp/%.o:
	$(CC) $(CFLAGS) -c $*.c $(OUTPUT_OPTION)


# Include dependency files here.
# If the files don't exist, this will fail silently and remake the dep files.
-include $(addprefix tmp/,$(SRC:.c=.d))



# remove the executable, .o files, and emacs backup files
clean: 
	rm -f tmp/*.o *~ ${NAME}
	make -C subdir clean

# remove the .d files too
# (Sometimes this is necessary if you manage to confuse Make)
clobber:
	rm -rf tmp
	make -C subdir clobber
