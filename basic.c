#include "basic.h"

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

void curs_mov(struct spos newpos)
{
	if (chkspos(newpos) == false) return;
	char t[16] = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
	sprintf(t, "\x1b[%d;%dH", newpos.r, newpos.c);
	str_append(__lascii->abuf, t, strlen(t));
	__lascii->cpos = newpos;
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

static void draw_obj(void)
{
	struct spos orig_cpos = __lascii->cpos;
	for (int i = 0; i < __lascii->obj_idmax; i++) {
		struct object *cobj = vector_get(__lascii->objects, i, struct object*);
		curs_mov(cobj->pos);
		str_append(__lascii->abuf, char2str(cobj->rep), 1);
	}
	curs_mov(orig_cpos);
	return;
}

static void draw_but(void)
{
	struct button cbut;
	for (int i = 0; i < __lascii->buttons->len; i++) {
		cbut = vector_get(__lascii->buttons, i, struct button);
		/* Draw the button */
		curs_mov(cbut.pos);
		for (int j = 1; j <= cbut.h; j++) {
			curs_mov(MKSPOS(cbut.pos.r + j, cbut.pos.c));
			buf_putstr("|");
			curs_mov(MKSPOS(cbut.pos.r + j, cbut.pos.c + cbut.w - 1));
			buf_putstr("|");
		}
		curs_mov(cbut.pos);
		for (int j = 0; j < cbut.w; j++)
			buf_putstr("-");
		curs_mov(MKSPOS(cbut.pos.r + cbut.h, cbut.pos.c));
		for (int j = 0; j < cbut.w; j++)
			buf_putstr("-");

		/* Draw the text */
		curs_mov(MKSPOS(cbut.pos.r + 1, cbut.pos.c + 1));
		buf_putstr(cbut.contents->str);

		/* And print the label */
		char tmp[MAX_BUTTONS];
		curs_mov(cbut.pos);
		sprintf(tmp, "%d", cbut.id);
		buf_putstr(tmp);
	}
}

static inline void buf_write(void)
{
	write(STDOUT, __lascii->abuf->str, __lascii->abuf->len);
	return;
}

void paintscreen(void)
{
	draw_obj();
	draw_but();
	buf_write();
	str_flush(__lascii->abuf);
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

			/* Ignore arrow keys */
			if (t[0] == '\x1b') {
				read(STDIN, &t, 2);
				if (t[1] == 'A' || t[1] == 'B' || t[1] == 'C' || t[1] == 'D') {
					scanlen -= 1;
					t[0] = '\0';
					t[1] = '\0';
					t[2] = '\0';
				}
			}
			if (__lascii->echo)
				write(STDOUT, t, 3);
			str_append(*store, t, 3);
		}
	}
	curs_mov(__lascii->cpos);
	return;
}

void clearscreen(void)
{
	str_append(__lascii->abuf, "\x1b[H\x1b[2J", 7);
	return;
}

void clearline(short int linenum)
{
	char t[12] = "\0\0\0\0\0\0\0\0\0\0\0";
	sprintf(t, "\x1b[%d;1H", linenum);
	str_append(__lascii->abuf, t, strlen(t));
	str_append(__lascii->abuf, "\x1b[K", 3);
	return;
}

void stdin_nonblock(void) {
	int flags = fcntl(STDIN, F_GETFL, 0);
	fcntl(STDIN, F_SETFL, flags | O_NONBLOCK);
}

void stdin_block(void) {
	int flags = fcntl(STDIN, F_GETFL, 0);
	fcntl(STDIN, F_SETFL, flags & ~O_NONBLOCK);
}
