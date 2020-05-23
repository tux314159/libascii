#ifndef INC_BASE
#include "../base.h"
#include "../basic.h"
#endif

short int button_create(struct spos butpos, char *sarr,
	size_t arrlen, short int w, short int h);
void button_del(short int id);
void button_bind(short int id, void_fnptr action); /* The function pointer action should be global! */
void button_call(short int id);