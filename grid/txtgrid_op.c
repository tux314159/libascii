#ifndef INC_GRID
#    include "grid.h"
#endif

void txt_grid_cell_add(char in, struct spos pos)
{
	_lascii->txtgrid[pos.r - 1][pos.c - 1] = in;
	return;
}

struct txt_gridtest txt_grid_cell_check(short int id, enum DIR dir)
{
	/* If it's at an edge, we return {true, NULL} else we return {false,
	 * <contents of the cell>} if it's not.
	 */
	struct object *cobj = vector_getptr(_lascii->objects, id - 1, struct object);
	struct txt_gridtest ret = {false, '\0'};

#define GRIDCELL_CONT(offr, offc) (_lascii->txtgrid[cobj->pos.r + offr][cobj->pos.c + offc])
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
