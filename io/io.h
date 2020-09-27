#ifndef INC_BASE
#    include "../base.h"
#endif

void buf_putstr(const char *str);
void curs_mov(const struct spos newpos);
void curs_invis(void);
void curs_vis(void);
void clearscreen(void);
void clearline(const short int linenum);
void stdin_nonblock(void);
void stdin_block(void);

char scankey(void);
void scanstr(string **store, const char delim);
