CFLAGS = -g -Wall -Wpedantic -Wextra -fPIC -o $@
CC = gcc $(CFLAGS)
OCC = $(CC) -c
AR = ar rcs $@

.PHONY : all

all : test dynamic static
	@echo -e "\033[0;31mRun this:  export LD_LIBRARY_PATH=\$${LD_LIBRARY_PATH}:$$(pwd)\033[0m"

dynamic : libascii.so

static : libascii.a

test : test.c libascii.so libmds/src/libmds.so
	$(CC) test.c -L. -lascii -Llibmds/src/ -lmds

libascii.a : init.o basic.o draw/*.o
	$(AR) $^

libascii.so : init.o basic.o draw/*.o
	$(CC) -shared -fPIC $^

init.o : init.c
basic.o : basic.c
draw/buf_putstr.o : draw/buf_putstr.c
draw/button.o : draw/button.c

libmds/src/libmds.so : FORCE
	$(MAKE) -C libmds/src/

clean : FORCE
	rm -rf *.o
	$(MAKE) -C libmds/src/ clean

FORCE :
