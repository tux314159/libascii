#include "basic.h"

static void draw_obj(void)
{
	struct spos orig_cpos = __lascii->cpos;
	for (int i = 0; i < __lascii->obj_idmax; i++) {
		struct object *cobj = __lascii->objects->data[i];
		curs_mov(cobj->pos);
		string_append(__lascii->abuf, char2str(cobj->rep));
	}
	curs_mov(orig_cpos);
	return;
}

void paintscreen(void)
{
	draw_obj();
	write(STDOUT, __lascii->abuf->str, __lascii->abuf->len);
	string_delete(__lascii->abuf, 0, __lascii->abuf->len);
	return;
}

