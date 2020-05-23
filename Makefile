CFLAGS = -g -Wall -fPIC -o $@
CC = gcc $(CFLAGS)
OCC = $(CC) -c
AR = ar rcs $@

.PHONY : all

all : test maze
	@echo "\033[0;31mRun this:  export LD_LIBRARY_PATH=\$${LD_LIBRARY_PATH}:$$(pwd)\033[0m"


dynamic : libascii.so

static : libascii.a

test : test.c libascii.so libmds/libmds.so
	$(CC) test.c -L. -lascii -Llibmds/ -lmds

maze : maze.c libascii.so libmds/libmds.so
	$(CC) maze.c -L. -lascii -Llibmds/ -lmds

libascii.a : globals.c init.o basic.o widgets/button.o objectsys/object.o
	$(AR) $^

libascii.so : globals.c init.o basic.o widgets/button.o objectsys/object.o
	$(CC) -shared -fPIC $^

libmds/libmds.so : FORCE
	$(MAKE) -C libmds/

libmds/libmds.a : FORCE
	$(MAKE) -C libmds/

git : FORCE
	git submodule init
	git submodule update --remote

clean : FORCE
	rm -rf *.o
	rm -rf */*.o
	$(MAKE) -C libmds/ cleanproper

cleanproper : clean
	rm -f test maze *.a *.so
	rm -rf libmds

FORCE :
