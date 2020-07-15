#ifndef INC_IO
#    include "io.h"
#endif

char scankey(void)
{
	char t[2] = "\0";
	read(STDIN, &t, 1);
	return t[0];
}

void scanstr(string **store, char delim)
{
	int scanlen = 0;
	char t[4] = "\0\0\0";
	for (;;) {
		read(STDIN, &t, 1);
		scanlen += 1;
		if (t[0] == delim)
			break;
		else {
			if (t[0] == 127 && scanlen != 0) {
				scanlen -= 1; /* The backspace character itself */
				if (scanlen != 0) {
					scanlen -= 1; /* Again; this is minusing off the previous character */
					t[0] = CTRL_KEY('H');
					t[1] = ' ';
					t[2] = CTRL_KEY('H');
				}
			}

			/* Ignore arrow keys */
			if (t[0] == '\x1b') {
				read(STDIN, &t, 2);
				if (t[1] == 'A' || t[1] == 'B' || t[1] == 'C' || t[1] == 'D') {
					scanlen -= 1;
					t[0] = '\0';
					t[1] = '\0';
					t[2] = '\0';
				}
			}
			if (__lascii->echo)
				write(STDOUT, t, 3);
			str_append(*store, t, 3);
		}
	}
	curs_mov(__lascii->cpos);
	return;
}

