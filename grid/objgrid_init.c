#ifndef INC_GRID
#    include "grid.h"
#endif

bool obj_grid_init(void)
{
	if (__lascii->objgrid)
		return false;

	__lascii->objgrid = malloc(__lascii->ws.ws_row * sizeof(struct vector**));
	for (int i = 0; i < __lascii->ws.ws_row; i++) {
		__lascii->objgrid[i] = malloc(__lascii->ws.ws_col * sizeof(struct vector*));
		for (int j = 0; j < __lascii->ws.ws_col; j++)
			__lascii->objgrid[i][j] = vector_create(sizeof(struct object));
	}

	return true;
}

bool obj_grid_deinit(void)
{
	if (!__lascii->objgrid)
		return false;

	for (int i = 0; i < __lascii->ws.ws_row; i++) {
		for (int j = 0; j < __lascii->ws.ws_col; j++)
			vector_del(__lascii->objgrid[i][j]);
		free(__lascii->objgrid[i]);
	}
	free(__lascii->objgrid);
	return true;
}
