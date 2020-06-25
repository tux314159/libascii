#ifndef INC_GRID
#    include "grid.h"
#endif

bool obj_grid_init(void)
{
	if (_lascii->objgrid)
		return false;

	_lascii->objgrid = malloc(_lascii->ws.ws_row * sizeof(struct vector**));
	for (int i = 0; i < _lascii->ws.ws_row; i++) {
		_lascii->objgrid[i] = malloc(_lascii->ws.ws_col * sizeof(struct vector*));
		for (int j = 0; j < _lascii->ws.ws_col; j++)
			_lascii->objgrid[i][j] = vector_create(sizeof(struct object));
	}

	return true;
}

bool obj_grid_deinit(void)
{
	if (!_lascii->objgrid)
		return false;

	for (int i = 0; i < _lascii->ws.ws_row; i++) {
		for (int j = 0; j < _lascii->ws.ws_col; j++)
			vector_del(_lascii->objgrid[i][j]);
		free(_lascii->objgrid[i]);
	}
	free(_lascii->objgrid);
	return true;
}
