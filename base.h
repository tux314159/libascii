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
#include "libmds/src/dynstr/headers/strop.h"
#include "libmds/src/vector/headers/vector.h"

/* Defining some useful structs */
struct curspos {
	short int r;
	short int c;
};

struct object {
	char rep;
	short int posr;
	short int posc;
};

struct libascii_stat {
	struct curspos cpos;
	struct termios init_termios;
	struct winsize ws;
	int echo; /* When receiving input, should I echo it on ouutput? */
	string *abuf;
};

/* Declaring globlal variables */
struct libascii_stat *_glob_lascii_stat;
/* Make this less of a pain */
#define _gls _glob_lascii_stat
