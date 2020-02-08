#include <stdio.h>
#include "api.h"

int main(void)
{
	startraw();
	curs_mov(getwinrows() / 2, getwincols() / 2 - 5);
	buf_putstr("libascii v0");
	curs_mov(getwinrows(), 0);
	buf_putstr("Press a key: ");
	buf_write();
	char rec = scankey();
	curs_mov(1, 1);
	buf_putstr((char[2]){rec, '\0'});
	buf_write();
	sleep(1);
	endraw();
	return 0;
}
