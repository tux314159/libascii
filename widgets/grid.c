#include "../base.h"
#include "widgets.h"

bool grid_init(void)
{
	if (_lascii->grid)
		return false;

	/* Not using vectors here because we don't need resizing or
	 * anything like that
	 */
	_lascii->grid = malloc(_lascii->ws.ws_row * sizeof(short int*));
	for (int i = 0; i < _lascii->ws.ws_row; i++)
		_lascii->grid[i] = calloc(_lascii->ws.ws_col, sizeof(short int));

	return true;
}

bool grid_deinit(void)
{
	if (!_lascii->grid)
		return false;

	for (int i = 0; i < _lascii->ws.ws_row; i++)
		free(_lascii->grid[i]);
	free(_lascii->grid);
	return true;
}
