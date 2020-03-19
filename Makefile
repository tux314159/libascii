CFLAGS = -g -Wall -fPIC -o $@
CC = gcc $(CFLAGS)
OCC = $(CC) -c
AR = ar rcs $@

.PHONY : all

all : test maze
	@echo -e "\033[0;31mRun this:  export LD_LIBRARY_PATH=\$${LD_LIBRARY_PATH}:$$(pwd)\033[0m"


dynamic : libascii.so

static : libascii.a

test : test.c libascii.so libmds/src/libmds.so
	$(CC) test.c -L. -lascii -Llibmds/src/ -lmds

maze : maze.c libascii.so libmds/src/libmds.so
	$(CC) maze.c -L. -lascii -Llibmds/src/ -lmds

libascii.a : init.o basic.o draw/buf_putstr.o draw/button.o objectsys/object.o
	$(AR) $^

libascii.so : init.o basic.o draw/buf_putstr.o draw/button.o objectsys/object.o
	$(CC) -shared -fPIC $^

init.o : init.c
basic.o : basic.c
draw/buf_putstr.o : draw/buf_putstr.c
draw/button.o : draw/button.c
objectsys/object.o : objectsys/object.c

libmds/src/libmds.so : FORCE
	$(MAKE) -C libmds/src/

libmds/src/libmds.a : FORCE
	$(MAKE) -C libmds/src/

git : FORCE
	git submodule update --remote

clean : FORCE
	rm -rf *.o
	rm -rf */*.o
	$(MAKE) -C libmds/src/ cleanproper

cleanproper : clean
	rm -f test maze *.a *.so
	rm -rf libmds

FORCE :
