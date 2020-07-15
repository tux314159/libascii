#ifndef INC_BASE
#    include "../base.h"
#endif

void buf_putstr(char *str);
void curs_mov(struct spos newpos);
void curs_invis(void);
void curs_vis(void);
void clearscreen(void);
void clearline(short int linenum);
void stdin_nonblock(void);
void stdin_block(void);

char scankey(void);
void scanstr(string **store, char delim);
