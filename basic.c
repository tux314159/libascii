#include "basic.h"

void curs_mov(short int newx, short int newy)
{
	char t[12] = "\0\0\0\0\0\0\0\0\0\0\0";
	sprintf(t, "\x1b[%d;%dH", newx, newy);
	str_append(_gls->abuf, t, strlen(t));
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
	char t[2];
	read(STDIN, &t, 1);
	return t[0];
}
