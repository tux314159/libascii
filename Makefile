WARNINGS = -W -Wall -Wextra -Wpedantic -pedantic -Wpointer-arith
DEBUG = -g
OPTIM = -O3 -march=native -mtune=native
CFLAGS = $(WARNINGS) $(DEBUG) $(OPTIM) -std=c99 -fsigned-char -fPIC -o $@
CC = gcc
AR = ar rcs $@
V = @

# FILES
BASE = globals.c init.o basic.o
IO = io/input.o io/output.o
WIDGETS = widgets/button.o
GRID = grid/objgrid_init.o grid/objgrid_op.o grid/txtgrid_init.o grid/txtgrid_op.o
OBJECTSYS = objectsys/object.o

LIBFILES = $(BASE) $(IO) $(WIDGETS) $(GRID) $(OBJECTSYS)

.PHONY : all clean cleanproper git dynamic static

all : test maze dynamic static

dynamic : libascii.so

static : libascii.a

test : test.o libascii.a libmds/libmds.a globals.o
	$V printf "Compiling and linking \033[1m$@\033[0m...\n"
	$V $(CC) $(CFLAGS) $^

maze : maze.o libascii.a libmds/libmds.a globals.o
	$V printf "Compiling and linking \033[1m$@\033[0m...\n"

libascii.a : $(LIBFILES)
	$V printf "Creating static library \033[1m$@\033[0m...\n"
	$V $(AR) $^

libascii.so : $(LIBFILES)
	$V printf "Creating shared library \033[1m$@\033[0m...\n"
	$V $(CC) $(CFLAGS) -shared -fPIC $^

libmds/libmds.a : FORCE
	$V printf "Building submodule \033[1m$@\033[0m...\n"
	$V $(MAKE) -s -C libmds/ libmds.a >/dev/null 2>&1

%.o : %.c
	$V printf "Compiling \033[1m$@\033[0m from $^...\n"
	$V $(CC) -c $(CFLAGS) $^

git : FORCE
	$V git submodule init
	$V git submodule update --remote

cleanproper : clean
	$V echo "Deep clean..."
	$V rm -f test maze *.a *.so
	$V rm -rf libmds
	$V echo "Sparkling clean!"

clean : FORCE
	$V echo "Cleaning..."
	$V find -name '*.o' -delete
	$V if [ -d libmds ]; then $(MAKE) -C libmds/ cleanproper; fi
	$V echo "Clean!"

FORCE :
