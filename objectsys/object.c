#include "object.h"

short int object_create(char rep, struct spos pos)
{
	__vector_pushback(_gls->objects, &(struct object){++_gls->obj_idmax, rep, pos});
	return _gls->obj_idmax;
}

void object_del(short int id)
{
	vector_erase(_gls->objects, id - 1);
	for (int i = id; i < _gls-> obj_idmax - 1; i++)
		vector_getptr(_gls->objects, i, struct object)->id -= 1;
	_gls->obj_idmax -= 1;
	return;
}

void object_mov(short int id, struct spos newpos)
{
	vector_getptr(_gls->objects, id - 1, struct object)->pos = newpos;
	return;
}