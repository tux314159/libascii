#ifndef INC_IO
#    include "io.h"
#endif

static inline bool chkspos(struct spos in)
{
	if (in.r <= 0) return false;
	if (in.r > __lascii->ws.ws_row) return false;
	if (in.c <= 0) return false;
	if (in.c > __lascii->ws.ws_col) return false;
	return true;
}

void buf_putstr(char *str)
{
	str_append(__lascii->abuf, str, strlen(str));
	return;
}

void curs_invis(void)
{
	str_append(__lascii->abuf, "\x1b[?25l", 6);
	return;
}

void curs_vis(void)
{
	str_append(__lascii->abuf, "\x1b[?25h", 6);
	return;
}

void curs_mov(struct spos newpos)
{
	if (chkspos(newpos) == false) return;
	char t[16] = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
	sprintf(t, "\x1b[%d;%dH", newpos.r, newpos.c);
	buf_putstr(t);
	__lascii->cpos = newpos;
	return;
}
