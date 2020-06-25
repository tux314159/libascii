#define INC_GRID
#ifndef INC_BASE
#    include "../base.h"
#endif

/* Directions */
enum DIR {N, NE, E, SE, S, SW, W, NW};

/* Init */
bool obj_grid_init(void);
bool obj_grid_deinit(void);
/* Operations */
struct object *obj_grid_cell_add(struct object obj, struct spos pos);
