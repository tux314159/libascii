#ifndef INC_GRID
#    include "grid.h"
#endif

bool txt_grid_init(void)
{
	if (__lascii->txtgrid)
		return false;

	__lascii->txtgrid = malloc(__lascii->ws.ws_row * sizeof(char*));
	for (int i = 0; i < __lascii->ws.ws_row; i++) {
		__lascii->txtgrid[i] = calloc(__lascii->ws.ws_col, sizeof(char));
	}

	return true;
}

bool txt_grid_deinit(void)
{
	if (!__lascii->txtgrid)
		return false;

	for (int i = 0; i < __lascii->ws.ws_row; i++)
		free(__lascii->txtgrid[i]);
	free(__lascii->txtgrid);
	return true;
}
