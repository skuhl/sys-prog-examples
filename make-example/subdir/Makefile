#NAME    = test

CC = gcc

INCLDIR = -I/usr/include
LIBDIR  =
LIBS    = -lm

SRC     = subfile.c
OBJ     = $(addprefix tmp/,$(SRC:.c=.o))


#OPT = -02 -Wall
OPT = -g -Wall

CFLAGS = ${OPT} ${INCLDIR} 
LDFLAGS = ${LIBDIR} ${LIBS}

# Describes how to link up the binary.
#$(NAME): $(OBJ)
#	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)

# NOTE: We don't actually tell Make how to make the .o files in this
# Makefile.  Instead, we use the fact that Make uses the variables set
# up above to automatically figure out how to generate the .o files.

# make dependency files
tmp/%.d: %.c
	@mkdir -p tmp
	@echo "Creating/recreating dependency file: $(@)"
	@set -e; $(CC) -MM $(CFLAGS) $< \
	| sed 's/\($*\)\.o[ :]*/tmp\/\1.o $* : /g' > $@; \
	[ -s $@ ] ||  rm -f $@

tmp/%.o:
	$(CC) $(CFLAGS) -c $*.c $(OUTPUT_OPTION)


# Include dependency files here.
# If the files don't exist, this will fail silently and remake the dep files.
-include $(addprefix tmp/,$(SRC:.c=.d))



# remove the executable, .o files, and emacs backup files
clean: 
	rm -f tmp/*.o *~ ${NAME}

# remove the .d files too
# (Sometimes this is necessary if you manage to confuse Make)
clobber:
	rm -rf tmp
