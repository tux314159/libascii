#define INC_BASE
#include <unistd.h>
#include <sys/ioctl.h>
#include <stddef.h>
#include <termios.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#ifndef INC_MACROS
#include "macros.h"
#endif
#include "libmds/src/dynstr/strop.h"

#define MAX_BUTTONS 50

/* Defining some useful structs */
struct spos { /* Screen position */
	short int r;
	short int c;
};

struct button {
	short int id;
	void (*action)(void);
};

struct libascii_stat {
	struct spos cpos;
	struct termios init_termios;
	struct winsize ws;
	int echo; /* When receiving input, should I echo it on output? */
	string *abuf;
	int idmax; /* Most recent object id */
	struct button *buttons; /* Not using libmds vectors here
	cos I don't know how */
};

/* Declaring globlal variables */
struct libascii_stat *_glob_lascii_stat;
/* Make this less of a pain */
#define _gls _glob_lascii_stat
#define NEWLINE '\r'
#define CTRL_KEY(k) ((k) & 0x1f)