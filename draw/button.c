#include "../base.h"
void make_button(struct spos butpos, string *s, int w, int h)
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
	curs_mov(r, c);
	return;
}
