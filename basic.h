#ifndef INC_BASE
#include "base.h"
#endif

char *char2str(char x);
void curs_mov(short int newr, short int newc);
void buf_write(void);
char scankey(void);
void scanstr(string **store, char delim);
void clearscreen(void);
void clearline(short int linenum);
#define getwinrows() (_gls->ws.ws_row)
#define getwincols() (_gls->ws.ws_col)
#define setecho() (_gls->echo = 1)
#define setnoecho() (_gls->echo = 0)
#define char2str(x) ((char[2]){(x), '\0'})
