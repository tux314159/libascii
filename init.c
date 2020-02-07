#include "init.h"

void libascii_init(void)
{
	_gls = malloc(sizeof(struct libascii_stat));
	_gls->abuf = str_create();
	/* Rows, columns are 1-indexed */
	_gls->cpos.x = 1;
	_gls->cpos.y = 1;
	/* Turn on 'raw mode' */
	struct termios orig, raw;
	tcgetattr(STDIN_FILENO, &orig);
	_gls->init_termios = orig;
	tcgetattr(STDIN_FILENO, &raw);
	raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	raw.c_oflag &= ~(OPOST);
	raw.c_cflag |= (CS8);
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
	return;
}

void libascii_exit(void)
{
	/* Restore 'cooked' mode */
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &(_gls->init_termios));
	/* Free memory */
	str_del(_gls->abuf);
	free(_gls);
	return;
}
