#ifndef INC_BASE
#include "../base.h"
#include "../basic.h"
#endif

void buf_putstr(char *str);
void make_button(struct spos butpos, char **sarr /* Array of C strings */,
	size_t arrlen, short int w, short int h);
