#include <stdio.h>
#include "api.h"

void say_hi(void)
{
	buf_putstr("HIIII");
	return;
}

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
	char *buttext[6] = {"Hello!", "Bye..."};
	button_create((struct spos){4, 5}, buttext, 2, 10, 3);
	button_bind(1, &say_hi);
	curs_mov(getwinrows() / 2, getwincols() / 2 - 5);
	buf_putstr("libascii v0");
	button_call(1);
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
