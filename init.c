#include "init.h"

void libascii_init(void)
{
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
	__lascii->objgrid = malloc(__lascii->ws.ws_row * sizeof(struct vector**));
	for (int i = 0; i < __lascii->ws.ws_row; i++) {
		__lascii->objgrid[i] = malloc(__lascii->ws.ws_col * sizeof(struct vector*));
		for (int j = 0; j < __lascii->ws.ws_col; j++)
			__lascii->objgrid[i][j] = vector_create(sizeof(struct object));

	}
	__lascii->txtgrid = malloc(__lascii->ws.ws_row * sizeof(char*));
	for (int i = 0; i < __lascii->ws.ws_row; i++) {
		__lascii->txtgrid[i] = calloc(__lascii->ws.ws_col, sizeof(char));
	}

	/* Use alternate buffer */
	write(STDOUT, "\x1b[?1049h", 8);

	/* Rows, columns are 1-indexed */
	__lascii->cpos.r = 1;
	__lascii->cpos.c = 1;

	/* Turn on 'raw mode' */
	struct termios orig, raw;
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
	for (int i = 0; i < __lascii->ws.ws_row; i++) {
		for (int j = 0; j < __lascii->ws.ws_col; j++)
			vector_del(__lascii->objgrid[i][j]);
		free(__lascii->objgrid[i]);
	}
	free(__lascii->objgrid);
	for (int i = 0; i < __lascii->ws.ws_row; i++)
		free(__lascii->txtgrid[i]);
	free(__lascii->txtgrid);

	/* And finally... */
	free(__lascii);
	return;
}
