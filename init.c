#include "init.h"

void libascii_init(void)
{
	/* Base */
	_lascii = malloc(sizeof(struct libascii_stat));
	_lascii->abuf = str_create();
	_lascii->echo = 0;
	/* Buttons */
	_lascii->buttons = vector_create(sizeof(struct button));
	_lascii->but_idmax = 0;
	/* Objects */
	_lascii->objects = vector_create(sizeof(struct object));
	_lascii->obj_idmax = 0;
	/* Use alternate buffer */
	write(STDOUT, "\x1b[?1049h", 8);
	/* Get window size */
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &(_lascii->ws));
	/* Rows, columns are 1-indexed */
	_lascii->cpos.r = 1;
	_lascii->cpos.c = 1;
	/* Turn on 'raw mode' */
	struct termios orig, raw;
	tcgetattr(STDIN_FILENO, &orig);
	_lascii->init_termios = orig;
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
	/* Go back */
	write(STDOUT, "\x1b[?1049l", 8);
	/* Restore 'cooked' mode */
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &(_lascii->init_termios));
	/* Free memory */
	str_del(_lascii->abuf);
	vector_del(_lascii->buttons);
	vector_del(_lascii->objects);
	free(_lascii);
	return;
}
