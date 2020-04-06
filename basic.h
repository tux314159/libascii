#ifndef INC_BASE
#include "base.h"
#endif

void buf_putstr(char *str);
void curs_mov(struct spos newpos);
void curs_invis(void);
void curs_vis(void);
void paintscreen(void);
char scankey(void);
void scanstr(string **store, char delim);
void clearscreen(void);
void clearline(short int linenum);
void stdin_nonblock(void);
void stdin_block(void);
#define getwinrows() (_gls->ws.ws_row)
#define getwincols() (_gls->ws.ws_col)
#define setecho() (_gls->echo = 1)
#define setnoecho() (_gls->echo = 0)
#define char2str(x) ((char[2]){(x), '\0'})
