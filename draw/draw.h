#ifndef INC_BASE
#include "../base.h"
#include "../basic.h"
#endif

void buf_putstr(char *str);
short int button_create(struct spos butpos, char **sarr /* Array of C strings */,
	size_t arrlen, short int w, short int h);
void button_bind(short int id, void_fnptr action); /* The function pointer action should be global! */
void button_call(short int id);
