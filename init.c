#include "init.h"

void libascii_init(void)
{
	_gls = malloc(sizeof(struct libascii_stat));
	_gls->abuf = str_create();
	_gls->buttons = vector_create(sizeof(struct button));
	_gls->echo = 0;
	_gls->but_idmax = 0;
	/* Use alternate buffer */
	write(STDOUT, "\x1b[?1049h", 8);
	/* Get window size */
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &(_gls->ws));
	/* Rows, columns are 1-indexed */
	_gls->cpos.r = 1;
	_gls->cpos.c = 1;
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
	/* Go back */
	write(STDOUT, "\x1b[?1049l", 8);
	/* Restore 'cooked' mode */
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &(_gls->init_termios));
	/* Free memory */
	str_del(_gls->abuf);
	vector_del(_gls->buttons);
	free(_gls);
	return;
}
