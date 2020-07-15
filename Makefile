WARNINGS = -W -Wall -Wextra -Wpedantic -pedantic -Wpointer-arith
DEBUG = -g
OPTIM = -O3 -march=native
CFLAGS = $(WARNINGS) $(DEBUG) $(OPTIM) -std=c99 -fPIC -o $@
CC = gcc
AR = ar rcs $@

# FILES
BASE = globals.c init.o basic.o
WIDGETS = widgets/button.o
GRID = grid/objgrid_init.o grid/objgrid_op.o grid/txtgrid_init.o grid/txtgrid_op.o
OBJECTSYS = objectsys/object.o

LIBFILES = $(BASE) $(WIDGETS) $(GRID) $(OBJECTSYS)

.PHONY : all clean cleanproper git dynamic static

all : test maze dynamic static

dynamic : libascii.so

static : libascii.a

test : test.c libascii.a libmds/libmds.a globals.c
	$(CC) $(CFLAGS) $^

maze : maze.c libascii.a libmds/libmds.a globals.c
	$(CC) $(CFLAGS) $^

libascii.a : $(LIBFILES)
	$(AR) $^

libascii.so : $(LIBFILES)
	$(CC) $(CFLAGS) -shared -fPIC $^

libmds/libmds.a : FORCE
	$(MAKE) -C libmds/

libmds/libmds.so : FORCE
	$(MAKE) -C libmds/

%.o : %.c
	$(CC) -c $(CFLAGS) $^

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
