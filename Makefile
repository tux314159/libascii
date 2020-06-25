CFLAGS = -g -Wall -Wextra -fPIC -o $@
CC = gcc $(CFLAGS)
OCC = $(CC) -c
AR = ar rcs $@

# FILES
BASE = globals.c init.o basic.o
WIDGETS = widgets/button.o
GRID = grid/objgrid_init.o grid/objgrid_op.o grid/txtgrid_init.c grid/txtgrid_op.o
OBJECTSYS = objectsys/object.o
LIBFILES = $(BASE) $(WIDGETS) $(GRID) $(OBJECTSYS)

.PHONY : all clean cleanproper git dynamic static

all : test maze dynamic static
	@echo "\033[0;31mRun this:  export LD_LIBRARY_PATH=\$${LD_LIBRARY_PATH}:$$(pwd)\033[0m"


dynamic : libascii.so

static : libascii.a

test : test.c libascii.a libmds/libmds.a globals.c
	$(CC) $^

maze : maze.c libascii.a libmds/libmds.a globals.c
	$(CC) $^

libascii.a : $(LIBFILES)
	$(AR) $^

libascii.so : $(LIBFILES)
	$(CC) -shared -fPIC $^

libmds/libmds.a : FORCE
	$(MAKE) -C libmds/

libmds/libmds.so : FORCE
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
