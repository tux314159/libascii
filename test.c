#include <stdio.h>
#include "api.h"

short int o1;
char *speeches[3] = {"Hi!", "Bye!", "No."};

int main(void)
{
	startraw();
	setecho();
	grid_init();

	/* Page 1 */
	curs_invis();
	o1 = object_create('@', MKSPOS(5, 1));
	curs_mov(MKSPOS(getwinrows(), 1));
	buf_putstr("Press a key: ");
	paintscreen();
	char rec = scankey();
	clearline(getwinrows());
	curs_mov(MKSPOS(1, 1));
	buf_putstr("You pressed '");
	buf_putstr(rec == NEWLINE ? "enter" : char2str(rec));
	buf_putstr("' (Press any key to continue)");
	paintscreen();
	scankey();

	clearscreen();
	/* Page 2 */
	object_mov(o1, MKSPOS(5, 2));
	curs_mov(MKSPOS(getwinrows(), 1));
	buf_putstr("Type something and press enter: ");
	curs_mov(MKSPOS(getwinrows(), strlen("Type something and press enter: ") + 1));
	curs_vis();
	paintscreen();
	string *t = str_create();
	scanstr(&t, NEWLINE);
	clearline(getwinrows());
	curs_mov(MKSPOS(1, 1));
	curs_invis();
	buf_putstr("You typed '");
	buf_putstr(t->str);
	buf_putstr("' (Press any key to continue)");
	paintscreen();
	scankey();

	clearscreen();
	/* Page 3 */
	object_mov(o1, MKSPOS(5, 3));
	buf_putstr("Pick something to say!");
	for (int i = 0; i < 3; i++)
		button_create(MKSPOS((i+1)*3, 2), speeches[i], 1, 1);

	paintscreen();
get_button_choice: ;;
	char choice = scankey();
	if (choice < '1' || choice > '3')
		goto get_button_choice;

	/* Exit code */
	curs_vis();
	paintscreen();
	object_del(o1);
	for (int i = 0; i < 3; i++)
		button_del(1);
	grid_deinit();
	endraw();
	str_del(t);
	return 0;
}
