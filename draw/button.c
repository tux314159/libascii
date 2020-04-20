#include "draw.h"
short int button_create(struct spos butpos, char **sarr /* Array of C strings */,
	size_t arrlen, short int w, short int h)
{
	w += 2;
	h += 1;

	struct spos orig_cpos = _gls->cpos;
	short int id;
	struct button cbut;

	id = ++_gls->but_idmax;
	if (id > MAX_BUTTONS) return -1; /* Error, too many buttons! */

	for (int i = 0; i < arrlen; i++)
		strcpy(cbut.strings[i], sarr[i]);
	cbut.id = id;
	cbut.w = w;
	cbut.h = h;
	cbut.pos = butpos;
	cbut.action = NULL;

	__vector_pushback(_gls->buttons, &cbut);
	curs_mov(orig_cpos);
	return id;
}

void button_bind(short int id, void_fnptr action)
{
	vector_getptr(_gls->buttons, id - 1, struct button)->action = action;
	return;
}

void button_call(short int id)
{
	vector_get(_gls->buttons, id - 1, struct button).action();
	return;
}
