#include <stdio.h>
#include "api.h"

int main(void)
{
	/* Page 1 */
	startraw();
	curs_mov(getwinrows() / 2, getwincols() / 2 - 5);
	buf_putstr("libascii v0");
	curs_mov(getwinrows(), 0);
	buf_putstr("Press a key: ");
	buf_write();
	char rec = scankey();
	curs_mov(1, 1);
	buf_putstr("You pressed '");
	buf_putstr((char[2]){rec, '\0'});
	buf_putstr("'    (Press any key to continue)");
	buf_write();
	scankey();


	clearscreen();
	curs_mov(getwinrows() / 2, getwincols() / 2 - 5);
	buf_putstr("libascii v0");
	curs_mov(getwinrows(), 0);
	buf_putstr("Type something and press enter: ");
	buf_write();
	/* Page 2 */
	string *t = str_create();
	scanstr(&t, '\r');
	curs_mov(1, 1);
	buf_putstr("You typed '");
	buf_putstr(t->str);
	buf_putstr("'    (Press any key to continue)");
	buf_write();
	scankey();
	endraw();
	str_del(t);
	return 0;
}
