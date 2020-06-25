#include <stdlib.h>
#include <unistd.h>

#ifndef INC_BASE
#    include "../base.h"
#endif
#ifndef INC_GRID
#    include "../grid/grid.h"
#endif

short int object_create(char rep, struct spos pos);
void object_del(short int id);
void object_mov(short int id, struct spos newpos);
struct object object_getattr(short int id);
