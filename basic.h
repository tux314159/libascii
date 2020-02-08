#ifndef INC_BASE
#include "base.h"
#endif

char *char2str(char x);
void curs_mov(short int newx, short int newy);
void buf_write(void);
char scankey(void);
#define getwinrows() _gls->ws.ws_row
#define getwincols() _gls->ws.ws_col
