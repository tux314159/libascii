#include <stdio.h>
#include "api.h"

const char *speeches[3] = {"Hi!", "Bye!", "No."};

int main(void)
{
	char rec;
	struct string t;

	libascii_init();
	setecho();

	/* Page 1 */
	curs_invis();
	curs_mov(MKSPOS(getwinrows(), 1));
	buf_putstr("Press a key: ");
	paintscreen();
	rec = scankey();
	clearline(getwinrows());
	curs_mov(MKSPOS(1, 1));
	buf_putstr("You pressed '");
	buf_putstr(rec == NEWLINE ? "enter" : char2str(rec));
	buf_putstr("' (Press any key to continue)");
	paintscreen();
	scankey();

	clearscreen();
	/* Page 2 */
	curs_mov(MKSPOS(getwinrows(), 1));
	buf_putstr("Type something and press enter: ");
	curs_mov(MKSPOS(getwinrows(), strlen("Type something and press enter: ") + 1));
	curs_vis();
	paintscreen();
	string_init(&t);
	scanstr(&t, NEWLINE);
	clearline(getwinrows());
	curs_mov(MKSPOS(1, 1));
	curs_invis();
	buf_putstr("You typed '");
	buf_putstr(t.str);
	buf_putstr("' (Press any key to continue)");
	paintscreen();
	scankey();

	clearscreen();

	/* Exit code */
	curs_vis();
	paintscreen();
	libascii_exit();
	string_deinit(&t);
	return 0;
}
