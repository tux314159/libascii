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

void buf_putstr(const char *str)
{
	string_append(__lascii->abuf, str);
	return;
}

void curs_invis(void)
{
	string_append(__lascii->abuf, "\x1b[?25l");
	return;
}

void curs_vis(void)
{
	string_append(__lascii->abuf, "\x1b[?25h");
	return;
}

void curs_mov(const struct spos newpos)
{
	char t[16];
	memset(t, '\0', sizeof(t) * sizeof(*t));

	if (chkspos(newpos) == false) return;
	sprintf(t, "\x1b[%hd;%hdH", newpos.r, newpos.c);
	buf_putstr(t);
	__lascii->cpos = newpos;
	return;
}

void clearscreen(void)
{
	string_append(__lascii->abuf, "\x1b[H\x1b[2J");
	return;
}

void clearline(const short int linenum)
{
	char t[12] = "\0\0\0\0\0\0\0\0\0\0\0";
	sprintf(t, "\x1b[%d;1H", linenum);
	string_append(__lascii->abuf, t);
	string_append(__lascii->abuf, "\x1b[K");
	return;
}

void stdin_nonblock(void)
{
	fcntl(STDIN, F_SETFL, fcntl(STDIN, F_GETFL, 0) | O_NONBLOCK);
}

void stdin_block(void)
{
	fcntl(STDIN, F_SETFL, fcntl(STDIN, F_GETFL, 0) & ~O_NONBLOCK);
}
