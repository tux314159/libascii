#ifndef INC_GRID
#    include "grid.h"
#endif

void txt_grid_cell_add(char in, struct spos pos)
{
	_lascii->txtgrid[pos.r - 1][pos.c - 1] = in;
	return;
}

char txt_grid_getcell(struct spos pos)
{
	/* Radically different interface from its object counterpart... */
	return _lascii->txtgrid[pos.r - 1][pos.c - 1];
}
