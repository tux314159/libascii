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
	return t[0];
}

void scanstr(string **store, char delim)
{
	int scanlen = 0;
	char t[4] = "\0\0\0";
	for (;;) {
		read(STDIN, &t, 1);
		scanlen += 1;
		if (t[0] == delim)
			break;
		else {
			if (t[0] == 127 && scanlen != 0) {
				scanlen -= 1; /* The backspace character itself */
				if (scanlen != 0) {
					scanlen -= 1; /* Again; this is minusing off the previous character */
					t[0] = CTRL_KEY('H');
					t[1] = ' ';
					t[2] = CTRL_KEY('H');
				}
			}

			/* Ignore special keys */
			if (t[0] == '\x1b') {
				read(STDIN, &t, 2);
				if (t[1] == 'A' || t[1] == 'B' || t[1] == 'C' || t[1] == 'D') {
					t[0] = '\0';
					t[1] = '\0';
					t[2] = '\0';
				}
			}
			if (_gls->echo)
				write(STDOUT, t, 3);
			str_append(*store, t, 3);
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

void clearline(short int linenum)
{
	char t[12] = "\0\0\0\0\0\0\0\0\0\0\0";
	sprintf(t, "\x1b[%d;1H", linenum);
	str_append(_gls->abuf, t, strlen(t));
	str_append(_gls->abuf, "\x1b[K", 3);
	return;
}
