#ifndef INC_BASE
#    include "base.h"
#endif
#ifndef INC_GRID
#    include "grid/grid.h"
#endif
#ifndef INC_IO
#    include "io/io.h"
#endif

void paintscreen(void);
#define getwinrows() (__lascii->ws.ws_row)
#define getwincols() (__lascii->ws.ws_col)
#define setecho() (__lascii->echo = 1)
#define setnoecho() (__lascii->echo = 0)
#define char2str(x) ((char[2]){(x), '\0'})

#define INC_BASIC
