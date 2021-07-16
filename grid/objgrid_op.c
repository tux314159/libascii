#ifndef INC_GRID
#    include "grid.h"
#endif

/* Where the actual objects are stored */

void obj_grid_cell_add(struct object obj, struct spos pos)
{
	vector_pushback(__lascii->objgrid[pos.r][pos.c], &obj);
}
