#include "object.h"

short int object_create(char rep, struct spos pos)
{
	const struct object obj = {++__lascii->obj_idmax, rep, pos};
	obj_grid_cell_add(obj, pos);
	return __lascii->obj_idmax;
}

void object_del(short int id)
{
	/* We look at objects[id-1], then search through the cell at that position and
	 * remove the one matching the id
	 */
	struct spos pos = vector_get(__lascii->objects, id - 1, struct object*)->pos;
	struct vector *cvec = __lascii->objgrid[pos.r][pos.c];
	/* Traverse that grid cell */
	for (int i = 0; i < cvec->len; i++) {
		if (vector_get(cvec, i, struct object).id == id)
			vector_erase(cvec, i);
	}
	/* Delete the reference in objlist */
	vector_erase(__lascii->objects, id - 1);
	__lascii->obj_idmax -= 1;
	return;
}

void object_mov(short int id, struct spos newpos)
{
	vector_get(__lascii->objects, id - 1, struct object*)->pos = newpos;
	return;
}
