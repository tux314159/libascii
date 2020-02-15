#include "basic.h"

void curs_mov(short int newr, short int newc)
{
	char t[12] = "\0\0\0\0\0\0\0\0\0\0\0";
	sprintf(t, "\x1b[%d;%dH", newr, newc);
	str_append(_gls->abuf, t, strlen(t));
	_gls->cpos.r = newr;
	_gls->cpos.c = newc;
	return;
}

void buf_write(void)
{
	write(STDOUT, _gls->abuf->str, _gls->abuf->len);
	str_flush(_gls->abuf);
	return;
}

char scankey(void)
{
	char t[2] = "\0";
	read(STDIN, &t, 1);
	if (_gls->echo)
		write(STDOUT, t, 1);
	curs_mov(_gls->cpos.r, _gls->cpos.c);
	return t[0];
}

void scanstr(string **store, char delim)
{
	char t[2] = "\0";
	for (;;) {
		read(STDIN, &t, 1);
		if (t[0] == delim)
			break;
		else {
			if (_gls->echo)
				write(STDOUT, t, 1);
			str_append(*store, t, 1);
		}
	}
	curs_mov(_gls->cpos.r, _gls->cpos.c);
	return;
}

void clearscreen(void)
{
	str_append(_gls->abuf, "\x1b[H\x1b[2J", 7);
	return;
}
