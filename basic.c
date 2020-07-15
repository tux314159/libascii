#include "basic.h"

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

void paintscreen(void)
{
	draw_obj();
	draw_but();
	write(STDOUT, __lascii->abuf->str, __lascii->abuf->len);
	str_flush(__lascii->abuf);
	return;
}

