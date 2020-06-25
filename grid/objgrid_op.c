#include "grid.h"

/* Where the actual objects are stored */

struct object *obj_grid_cell_add(struct object obj, struct spos pos)
{
	return (struct object*)__vector_pushback(_lascii->objgrid[pos.r][pos.c], &obj);
}
