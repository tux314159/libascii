#include "draw.h"
void make_button(struct spos butpos, char **sarr /* Array of C strings */,
	size_t arrlen, short int w, short int h)
{
	int r = _gls->cpos.r;
	int c = _gls->cpos.c;

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

	curs_mov(r, c);
	return;
}