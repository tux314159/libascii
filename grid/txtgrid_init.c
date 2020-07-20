#ifndef INC_GRID
#    include "grid.h"
#endif

char** txt_grid_init(void)
{
	char **retptr = malloc(__lascii->ws.ws_row * sizeof(char*));
	for (int i = 0; i <= __lascii->ws.ws_row; i++) {
		retptr[i] = malloc(__lascii->ws.ws_col * sizeof(char));
		memset(retptr[i], ' ', __lascii->ws.ws_col * sizeof(char));
		retptr[i][__lascii->ws.ws_col] = '\0';
	}

	return retptr;
}

void txt_grid_deinit(void)
{
	for (int i = 0; i < __lascii->ws.ws_row; i++)
		free(__lascii->txtgrid[i]);
	free(__lascii->txtgrid);
}
