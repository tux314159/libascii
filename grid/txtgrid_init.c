#ifndef INC_GRID
#    include "grid.h"
#endif

bool txt_grid_init(void)
{
	if (_lascii->objgrid)
		return false;

	_lascii->objgrid = malloc(_lascii->ws.ws_row * sizeof(struct vector**));
	for (int i = 0; i < _lascii->ws.ws_row; i++) {
		_lascii->objgrid[i] = malloc(_lascii->ws.ws_col * sizeof(struct vector*));
		memset(_lascii->txtgrid, 0, _lascii->ws.ws_col * sizeof(char));
	}

	return true;
}

bool txt_grid_deinit(void)
{
	if (!_lascii->objgrid)
		return false;

	for (int i = 0; i < _lascii->ws.ws_row; i++)
		free(_lascii->objgrid[i]);
	free(_lascii->txtgrid);
	return true;
}
