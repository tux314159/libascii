#include "object.h"

short int object_create(char rep, struct spos pos)
{
	struct object obj = {++_lascii->obj_idmax, rep, pos};
	vector_pushback(_lascii->objects, obj_grid_cell_add(obj, pos), struct object*);
	return _lascii->obj_idmax;
}

void object_del(short int id)
{
	/* We look at objects[id-1], then search through the cell at that position and
	 * remove the one matching the id
	 */
	struct spos pos = vector_get(_lascii->objects, id - 1, struct object*)->pos;
	struct vector *cvec = _lascii->objgrid[pos.r][pos.c];
	/* Traverse that grid cell */
	for (int i = 0; i < cvec->len; i++) {
		if (vector_get(cvec, i, struct object).id == id)
			vector_erase(cvec, i);
	}
	/* Delete the reference in objlist */
	vector_erase(_lascii->objects, id - 1);
	_lascii->obj_idmax -= 1;
	return;
}

void object_mov(short int id, struct spos newpos)
{
	vector_get(_lascii->objects, id - 1, struct object*)->pos = newpos;
	return;
}

struct object object_getattr(short int id)
{
	return *vector_get(_lascii->objects, id - 1, struct object*);
}

struct gridtest object_checkcell(short int id, enum DIR dir)
{
	/* If it's at an edge, we return {true, NULL} else we return {false,
	 * <pointer to the vector in that cell>} if it's not.
	 *
	 * DO NOT MODIFY THE VECTOR!
	 */
	struct object *cobj = vector_getptr(_lascii->objects, id - 1, struct object);
	struct gridtest ret = {false, NULL};

#define GRIDCELL_CONT(offr, offc) (_lascii->objgrid[cobj->pos.r + offr][cobj->pos.c + offc])
	switch (dir) {
	case N:
		if (cobj->pos.r == 1)
			ret.edgep = true;
		else
			ret.contents = GRIDCELL_CONT(-1, 0);
		break;

	case NE:
		if (cobj->pos.r == 1 || cobj->pos.c == _lascii->ws.ws_col)
			ret.edgep = true;
		else
			ret.contents = GRIDCELL_CONT(-1, 1);
		break;

	case E:
		if (cobj->pos.c == _lascii->ws.ws_col)
			ret.edgep = true;
		else
			ret.contents = GRIDCELL_CONT(0, 1);
		break;

	case SE:
		if (cobj->pos.r == _lascii->ws.ws_row || cobj->pos.c == _lascii->ws.ws_col)
			ret.edgep = true;
		else
			ret.contents = GRIDCELL_CONT(1, 1);
		break;

	case S:
		if (cobj->pos.r == _lascii->ws.ws_row)
			ret.edgep = true;
		else
			ret.contents = GRIDCELL_CONT(1, 0);
		break;

	case SW:
		if (cobj->pos.r == _lascii->ws.ws_row || cobj->pos.c == 1)
			ret.edgep = true;
		else
			ret.contents = GRIDCELL_CONT(1, -1);
		break;

	case W:
		if (cobj->pos.c == 1)
			ret.edgep = true;
		else
			ret.contents = GRIDCELL_CONT(0, -1);
		break;

	case NW:
		if (cobj->pos.r == 1 || cobj->pos.c == 1)
			ret.edgep = true;
		else
			ret.contents = GRIDCELL_CONT(-1, -1);
		break;
	}
	return ret;
#undef GRIDCELL_CONT
}
