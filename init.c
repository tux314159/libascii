#include "init.h"

void libascii_init(void)
{
	struct termios orig, raw;

	/* Base */
	__lascii = malloc(sizeof(struct libascii_stat));
	__lascii->abuf = str_create();
	__lascii->echo = 0;

	/* Buttons */
	__lascii->buttons = vector_create(sizeof(struct button));
	__lascii->but_idmax = 0;

	/* Objects */
	__lascii->objects = vector_create(sizeof(struct object*));
	__lascii->obj_idmax = 0;

	/* Get window size */
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &(__lascii->ws));

	/* Grids */
	__lascii->objgrid = obj_grid_init();
	__lascii->txtgrid = txt_grid_init();
	/* Use alternate buffer */
	write(STDOUT, "\x1b[?1049h", 8);

	/* Rows, columns are 1-indexed */
	__lascii->cpos.r = 1;
	__lascii->cpos.c = 1;

	/* Turn on 'raw mode' */
	tcgetattr(STDIN_FILENO, &orig);
	__lascii->init_termios = orig;
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
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &(__lascii->init_termios));
	/* Free memory */
	str_del(__lascii->abuf);
	vector_del(__lascii->buttons);
	vector_del(__lascii->objects);
	/* Free the grids */
	obj_grid_deinit();
	txt_grid_deinit();
	/* And finally... */
	free(__lascii);
	return;
}
