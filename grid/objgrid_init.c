#ifndef INC_GRID
#    include "grid.h"
#endif

struct vector ***obj_grid_init(void)
{
	struct vector ***retptr = malloc(__lascii->ws.ws_row * sizeof(struct vector**));
	for (int i = 0; i < __lascii->ws.ws_row; i++) {
		retptr[i] = malloc(__lascii->ws.ws_col * sizeof(struct vector*));
		for (int j = 0; j < __lascii->ws.ws_col; j++)
			retptr[i][j] = vector_create(sizeof(struct object));
	}

	return retptr;
}

void obj_grid_deinit(void)
{
	for (int i = 0; i < __lascii->ws.ws_row; i++) {
		for (int j = 0; j < __lascii->ws.ws_col; j++)
			vector_del(__lascii->objgrid[i][j]);
		free(__lascii->objgrid[i]);
	}
	free(__lascii->objgrid);
}
