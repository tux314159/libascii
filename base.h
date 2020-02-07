#define INC_BASE
#include <unistd.h>
#include <stddef.h>
#include <termios.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#ifndef INC_MACROS
#include "macros.h"
#endif
#include "libmds/src/dynstr/headers/strop.h"

/* Defining some useful structs */
struct curspos {
	short int x;
	short int y;
};

struct libascii_stat {
	struct curspos cpos;
	struct termios init_termios;
	string *abuf;
};

/* Declaring globlal variables */
struct libascii_stat *_glob_lascii_stat;
/* Make this less of a pain */
#define _gls _glob_lascii_stat
