#ifndef INC_GRID
#    include "grid.h"
#endif

bool txt_grid_init(void)
{
	if (_lascii->txtgrid)
		return false;

	_lascii->txtgrid = malloc(_lascii->ws.ws_row * sizeof(char*));
	for (int i = 0; i < _lascii->ws.ws_row; i++) {
		_lascii->txtgrid[i] = calloc(_lascii->ws.ws_col, sizeof(char));
	}

	return true;
}

bool txt_grid_deinit(void)
{
	if (!_lascii->txtgrid)
		return false;

	for (int i = 0; i < _lascii->ws.ws_row; i++)
		free(_lascii->txtgrid[i]);
	free(_lascii->txtgrid);
	return true;
}
