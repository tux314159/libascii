#include "object.h"
#include <stdlib.h>
#include <unistd.h>

short int object_create(char rep, struct spos pos)
{
	__vector_pushback(_lascii->objects, &(struct object)
			{++_lascii->obj_idmax, rep, pos});
	_lascii->grid[pos.r][pos.c] = _lascii->obj_idmax;
	return _lascii->obj_idmax;
}

void object_del(short int id)
{
	struct spos objpos = vector_getptr(_lascii->objects, id - 1, struct object)->pos;
	_lascii->grid[objpos.r][objpos.c] = 0;
	vector_erase(_lascii->objects, id - 1);
	for (int i = id; i < _lascii-> obj_idmax - 1; i++)
		vector_getptr(_lascii->objects, i, struct object)->id -= 1;
	_lascii->obj_idmax -= 1;
	return;
}

void object_mov(short int id, struct spos newpos)
{
	struct object *cobj = vector_getptr(_lascii->objects, id - 1, struct object);
	cobj->pos = newpos;
	_lascii->grid[cobj->pos.r][cobj->pos.c] = 0;
	_lascii->grid[newpos.r][newpos.c] = cobj->id;
	return;
}

struct object object_getattr(short int id)
{
	return vector_get(_lascii->objects, id - 1, struct object);
}

struct gridtest object_checkcell(short int id, enum DIR dir)
{
	/* If it's at a wall, we return {true, 0}
	 * else we return {false, WHATEVER}
	 * EXCEPT if dir == ALL, then we return either
	 * {false, 0} for ALL CLEAR and {false, 1} for
	 * not ALL CLEAR
	 */
	struct object *cobj = vector_getptr(_lascii->objects, id - 1, struct object);
	struct gridtest ret = {false, 0};
	switch (dir) {
	case N:
		if (cobj->pos.r == 1)
			ret.edgep = true;
		else
			ret.contents = _lascii->grid[cobj->pos.r - 2][cobj->pos.c - 1];
		break;
		
	case NE:
		if (cobj->pos.r == 1 || cobj->pos.c == _lascii->ws.ws_col)
			ret.edgep = true;
		else
			ret.contents = _lascii->grid[cobj->pos.r - 2][cobj->pos.c];
		break;

	case E:
		if (cobj->pos.c == _lascii->ws.ws_col)
			ret.edgep = true;
		else
			ret.contents = _lascii->grid[cobj->pos.r - 1][cobj->pos.c];
		break;

	case SE:
		if (cobj->pos.r == _lascii->ws.ws_row || cobj->pos.c == _lascii->ws.ws_col)
			ret.edgep = true;
		else
			ret.contents = _lascii->grid[cobj->pos.r][cobj->pos.c];
		break;

	case S:
		if (cobj->pos.r == _lascii->ws.ws_row)
			ret.edgep = true;
		else
			ret.contents = _lascii->grid[cobj->pos.r][cobj->pos.c - 1];
		break;

	case SW:
		if (cobj->pos.r == _lascii->ws.ws_row || cobj->pos.c == 1)
			ret.edgep = true;
		else
			ret.contents = _lascii->grid[cobj->pos.r][cobj->pos.c - 2];
		break;

	case W:
		if (cobj->pos.c == 1)
			ret.edgep = true;
		else
			ret.contents = _lascii->grid[cobj->pos.r - 1][cobj->pos.c - 2];
		break;

	case NW:
		if (cobj->pos.r == 1 || cobj->pos.c == 1)
			ret.edgep = true;
		else
			ret.contents = _lascii->grid[cobj->pos.r -2][cobj->pos.c - 2];
		break;

	case ALL:
		/* Whee! */
		if (cobj->pos.r == 1 || cobj->pos.c == 1 ||
				cobj->pos.r == _lascii->ws.ws_col ||
				cobj->pos.c == _lascii->ws.ws_row)
			ret.edgep = true;
		else
			ret.contents = _lascii->grid[cobj->pos.r][cobj->pos.c] ||
				_lascii->grid[cobj->pos.r - 1][cobj->pos.c] ||
				_lascii->grid[cobj->pos.r - 2][cobj->pos.c] ||
				_lascii->grid[cobj->pos.r][cobj->pos.c - 1] ||
				_lascii->grid[cobj->pos.r][cobj->pos.c - 2] ||
				_lascii->grid[cobj->pos.r - 1][cobj->pos.c - 2] ||
				_lascii->grid[cobj->pos.r - 2][cobj->pos.c - 1];
		break;
	}
	return ret;
}
