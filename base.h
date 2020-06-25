#define INC_BASE
#include <unistd.h>
#include <sys/ioctl.h>
#include <stddef.h>
#include <termios.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#ifndef INC_MACROS
#    include "macros.h"
#endif
#include "libmds/libmds.h"

/* Macros and typedefs */
#define MAX_BUTTONS 50
typedef void (*void_fnptr)(void);

/* Defining some essential structs */
struct spos { /* Screen position */
	short int r;
	short int c;
};

struct button {
	short int id;
	short int w;
	short int h;
	struct spos pos;
	string *contents;
	size_t arrlen;
	void_fnptr action;
};

struct object {
	short int id;
	char rep;
	struct spos pos;
};

struct gridtest {
	bool edgep;
	struct vector *contents;
};

struct libascii_stat {
	struct spos cpos;
	struct termios init_termios;
	struct winsize ws;
	int echo; /* When receiving input, should I echo it on output? */
	string *abuf;
	struct vector *buttons;
	short int but_idmax; /* Most recent button id */
	short int obj_idmax; /* Most recent object id */
	struct vector *objects;
	struct vector ***objgrid; /* The grid itself */
};

/* Declaring globlal variables */
extern struct libascii_stat *_lascii;
#define NEWLINE '\r'
#define CTRL_KEY(k) ((k) & 0x1f)
#define MKSPOS(x, y) ((struct spos){(x), (y)})
