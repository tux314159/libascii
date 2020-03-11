#include "draw.h"
short int button_create(struct spos butpos, char **sarr /* Array of C strings */,
	size_t arrlen, short int w, short int h)
{
	int r = _gls->cpos.r;
	int c = _gls->cpos.c;
	short int id;
	struct button cbut;

	curs_mov(butpos.r, butpos.c);
	for (int i = 0; i < w; i++) buf_putstr("-");
	curs_mov(butpos.r + h + 1, butpos.c);
	for (int i = 0; i < w; i++) buf_putstr("-");
	for (int i = 1; i <= h; i++) {
		curs_mov(butpos.r + i, butpos.c);
		buf_putstr("|");
		curs_mov(butpos.r + i, butpos.c + w - 1);
		buf_putstr("|");
	}

	for (int i = 0; i < arrlen && i < h; i++) {
		curs_mov(butpos.r + i + 1, butpos.c + 1);
		buf_putstr(sarr[i]);
	}

	id = ++_gls->idmax;
	if (id > MAX_BUTTONS) return -1; /* Error! */
	cbut.id = id;
	cbut.action = NULL;
	_gls->buttons[id - 1] = cbut;
	curs_mov(r, c);
	return id;
}

void button_bind(short int id, void (*action)(void))
{
	_gls->buttons[id - 1].action = action;
	return;
}

void button_call(short int id)
{
	_gls->buttons[id - 1].action();
	return;
}