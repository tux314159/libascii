#ifndef INC_BASE
#include "../base.h"
#endif

/* Directions */
enum DIR {N, NE, E, SE, S, SW, W, NW, ALL};

short int object_create(char rep, struct spos pos);
void object_del(short int id);
void object_mov(short int id, struct spos newpos);
struct object object_getattr(short int id);
struct gridtest object_celltest(short int id, enum DIR dir);
