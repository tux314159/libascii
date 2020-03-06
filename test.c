#include <stdio.h>
#include "api.h"

int main(void)
{
	startraw();
	setecho();
	
	/* Page 1 */
	curs_mov(getwinrows() / 2, getwincols() / 2 - 5);
	buf_putstr("libascii v0");
	curs_mov(getwinrows(), 0);
	buf_putstr("Press a key: ");
	buf_write();
	char rec = scankey();
	clearline(getwinrows());
	curs_mov(1, 1);
	buf_putstr("You pressed '");
	buf_putstr(rec == NEWLINE ? "enter" : char2str(rec));
	buf_putstr("' (Press any key to continue)");
	buf_write();
	scankey();


	clearscreen();


	/* Page 2 */
	make_button((struct spos){4, 5}, "Hi!", 10, 1);
	curs_mov(getwinrows() / 2, getwincols() / 2 - 5);
	buf_putstr("libascii v0");
	curs_mov(getwinrows(), 0);
	buf_putstr("Type something and press enter: ");
	buf_write();
	string *t = str_create();
	scanstr(&t, NEWLINE);
	clearline(getwinrows());
	curs_mov(1, 1);
	buf_putstr("You typed '");
	buf_putstr(t->str);
	buf_putstr("' (Press any key to continue)");
	buf_write();
	scankey();

	/* Exit code */
	endraw();
	str_del(t);
	return 0;
}
