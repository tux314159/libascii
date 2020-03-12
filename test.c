#include <stdio.h>
#include "api.h"

short int c1, c2, c3, o1;
char *speeches[3] = {"Hi!", "Bye!", "No."};

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
	o1 = object_create('@', MKSPOS(5, 1));
	curs_mov(getwinrows() / 2, getwincols() / 2 - 5);
	buf_putstr("libascii v0");
	curs_mov(getwinrows(), 0);
	buf_putstr("Press a key: ");
	paintscreen();
	char rec = scankey();
	clearline(getwinrows());
	curs_mov(1, 1);
	buf_putstr("You pressed '");
	buf_putstr(rec == NEWLINE ? "enter" : char2str(rec));
	buf_putstr("' (Press any key to continue)");
	paintscreen();
	scankey();

	clearscreen();
	/* Page 2 */
	object_mov(o1, MKSPOS(5, 2));
	curs_mov(getwinrows() / 2, getwincols() / 2 - 5);
	buf_putstr("libascii v0");
	curs_mov(getwinrows(), 0);
	buf_putstr("Type something and press enter: ");
	curs_mov(getwinrows(), strlen("Type something and press enter: ") + 2);
	paintscreen();
	string *t = str_create();
	scanstr(&t, NEWLINE);
	clearline(getwinrows());
	curs_mov(1, 1);
	buf_putstr("You typed '");
	buf_putstr(t->str);
	buf_putstr("' (Press any key to continue)");
	paintscreen();
	scankey();

	clearscreen();
	/* Page 3 */
	object_mov(o1, MKSPOS(5, 2));
	buf_putstr("Pick something to say!");
	for (int i = 0; i < 3; i++)
		button_create(MKSPOS((i+1)*3, 2), speeches+i, 1, strlen(speeches[i]), 1);
		
	paintscreen();
get_button_choice: ;;
	char choice = scankey();
	if (choice < '1' || choice > '3')
		goto get_button_choice;

	/* Exit code */
	endraw();
	str_del(t);
	return 0;
}
