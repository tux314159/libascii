#ifndef INC_GRID
#    include "grid.h"
#endif

/* Where the actual objects are stored */

struct object *obj_grid_cell_add(struct object obj, struct spos pos)
{
	return (struct object*)__vector_pushback(__lascii->objgrid[pos.r][pos.c], &obj);
}

struct obj_gridtest obj_grid_cell_check(short int id, enum DIR dir)
{
	/* If it's at an edge, we return {true, NULL} else we return {false,
	 * <pointer to the vector in that cell>} if it's not.
	 *
	 * DO NOT MODIFY THE VECTOR!
	 */
	struct object *cobj = vector_getptr(__lascii->objects, id - 1, struct object);
	struct obj_gridtest ret = {false, NULL};

#define GRIDCELL_CONT(offr, offc) (__lascii->objgrid[cobj->pos.r + offr][cobj->pos.c + offc])
	switch (dir) {
	case N:
		if (cobj->pos.r == 1)
			ret.edgep = true;
		else
			ret.contents = GRIDCELL_CONT(-1, 0);
		break;

	case NE:
		if (cobj->pos.r == 1 || cobj->pos.c == __lascii->ws.ws_col)
			ret.edgep = true;
		else
			ret.contents = GRIDCELL_CONT(-1, 1);
		break;

	case E:
		if (cobj->pos.c == __lascii->ws.ws_col)
			ret.edgep = true;
		else
			ret.contents = GRIDCELL_CONT(0, 1);
		break;

	case SE:
		if (cobj->pos.r == __lascii->ws.ws_row || cobj->pos.c == __lascii->ws.ws_col)
			ret.edgep = true;
		else
			ret.contents = GRIDCELL_CONT(1, 1);
		break;

	case S:
		if (cobj->pos.r == __lascii->ws.ws_row)
			ret.edgep = true;
		else
			ret.contents = GRIDCELL_CONT(1, 0);
		break;

	case SW:
		if (cobj->pos.r == __lascii->ws.ws_row || cobj->pos.c == 1)
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
