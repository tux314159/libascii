#define INC_GRID
#ifndef INC_BASE
#    include "../base.h"
#endif

/* Directions */
enum DIR {N, NE, E, SE, S, SW, W, NW};

/* Init */
struct vector ***obj_grid_init(void);
void obj_grid_deinit(void);
char **txt_grid_init(void);
void txt_grid_deinit(void);

/* Operations */
struct object *obj_grid_cell_add(struct object obj, struct spos pos);
struct obj_gridtest obj_grid_cell_check(short int id, enum DIR dir);
void txt_grid_cell_add(char in, struct spos pos);
char txt_grid_getcell(struct spos pos);
