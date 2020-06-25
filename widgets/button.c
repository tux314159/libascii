#include "widgets.h"
short int button_create(struct spos butpos, char *sarr, short int w, short int h)
{
	w += 2;
	h += 1;

	short int id;
	struct button cbut;

	id = ++_lascii->but_idmax;

	cbut.contents = str_create();
	cbut.id = id;
	cbut.w = w;
	cbut.h = h;
	cbut.pos = butpos;
	str_append(cbut.contents, sarr, strlen(sarr));
	cbut.action = NULL;

	__vector_pushback(_lascii->buttons, &cbut);
	return id;
}

void button_del(short int id)
{
	vector_erase(_lascii->buttons, id - 1);
	return;
}

void button_bind(short int id, void_fnptr action)
{
	vector_getptr(_lascii->buttons, id - 1, struct button)->action = action;
	return;
}

void button_call(short int id)
{
	vector_get(_lascii->buttons, id - 1, struct button).action();
	return;
}
