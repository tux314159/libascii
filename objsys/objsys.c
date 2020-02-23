#include "objsys.h"

int obj_create(char rep, int posr, int posc)
{
	struct object new;
	new.rep = rep;
	new.posr = posr;
	new.posc = posc;
	_gls->idmax += 1;
	new.id = _gls->idmax;
	vector_pushback(_gls->objlist, &new, struct object*);
	return new.id;
}

void obj_del(int id)
{
	vector_erase(_gls->objlist, id - 1);
	for (int i = id - 1; i < _gls->objlist->len; i++)
		vector_get(_gls->objlist, i, int) -= 1;
	_gls->idmax -= 1;
	return;
}
