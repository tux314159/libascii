CFLAGS = -g -o $@
CC = gcc $(CFLAGS)
OCC = $(CC) -c
AR = ar rcs $@

test : test.c libascii.a libmds/src/libmds.a
	$(CC) $^

libascii.a : init.o basic.o draw.o
	$(AR) $^

init.o : init.c
	$(OCC) $<

basic.o : basic.c
	$(OCC) $<

draw.o : draw/buf_putstr.c
	$(OCC) $^

clean : FORCE
	rm -rf *.o

FORCE :
