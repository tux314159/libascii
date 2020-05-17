#include "object.h"

short int object_create(char rep, struct spos pos)
{
	__vector_pushback(_lascii->objects, &(struct object){
			++_lascii->obj_idmax,
			rep, pos});
	return _lascii->obj_idmax;
}

void object_del(short int id)
{
	vector_erase(_lascii->objects, id - 1);
	for (int i = id; i < _lascii-> obj_idmax - 1; i++)
		vector_getptr(_lascii->objects, i, struct object)->id -= 1;
	_lascii->obj_idmax -= 1;
	return;
}

void object_mov(short int id, struct spos newpos)
{
	vector_getptr(_lascii->objects, id - 1, struct object)->pos = newpos;
	return;
}

struct object object_getattr(short int id)
{
	return vector_get(_lascii->objects, id - 1, struct object);
}
