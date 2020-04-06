#define INC_BASE
#include <unistd.h>
#include <sys/ioctl.h>
#include <stddef.h>
#include <termios.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#ifndef INC_MACROS
#include "macros.h"
#endif
#include "libmds/src/libmds.h"

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
	void_fnptr action;
};

struct object {
	short int id;
	char rep;
	struct spos pos;
	struct vector *actions;
	short int act_max;
};

struct libascii_stat {
	struct spos cpos;
	struct termios init_termios;
	struct winsize ws;
	int echo; /* When receiving input, should I echo it on output? */
	string *abuf;
	struct vector *buttons;
	int but_idmax; /* Most recent button id */
	int obj_idmax; /* Most recent object id */
	struct vector *objects;
};

/* Declaring globlal variables */
struct libascii_stat *_glob_lascii_stat;
/* Make this less of a pain */
#define _gls _glob_lascii_stat
#define NEWLINE '\r'
#define CTRL_KEY(k) ((k) & 0x1f)
#define MKSPOS(x, y) ((struct spos){(x), (y)})
