#include <stdio.h>
#include <time.h>
#include <errno.h>
#include "api.h"

#define CURR curr-1 /* because screen is 1-indexed but the array is 0-indexed */
#define CURC curc-1 /* ditto */

int main(int argc, char **argv)
{
	char map[200][250];
	char scan = '\0';
	short int curr, curc;
	char *wall_chars = NULL;
	size_t wall_chars_n = 0;
	char goal;

	memset(map, '\0', sizeof(char) * 200 * 250);

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <mapfile>\n", argv[0]);
		exit(1);
	}
	FILE *mapfile = fopen(argv[1], "r");
	perror("Opening map file");
	if (errno != 0)
		exit(2);

	/* Read the map */
	{
		getline(&wall_chars, &wall_chars_n, mapfile);
		wall_chars[strlen(wall_chars)-1] = '\0'; /* strip newline */
		goal = fgetc(mapfile);
		fgetc(mapfile); /* skip the next newline */
		fscanf(mapfile, "%hd%hd", &curr, &curc);
		fgetc(mapfile); /* skip the next newline */

		char t = '\0';
		int r = 0, c = 0;
		while ((t = fgetc(mapfile)) != EOF) {
			if (t == '\n') {
				r++;
				c = 0;
				continue;
			}
			map[r][c] = t;
			c++;
		}
		fclose(mapfile);
	}

	libascii_init();
	obj_grid_init();
	object_create('@', MKSPOS(curr, curc));
	time_t starttime = time(NULL);
	int won = 0;

	for (int i = 0; i < getwinrows(); i++) {
		for (int j = 0; j < getwincols(); j++) {
			curs_mov(MKSPOS(i+1, j+1));
			buf_putstr(char2str(map[i][j]));
		}
	}
	curs_mov(MKSPOS(curr, curc));
	paintscreen();

	while (scan != 'q') {
		scan = scankey();
		curs_mov(MKSPOS(curr, curc));
		buf_putstr(char2str(' '));
		switch (scan) {
		case 'h':
			if (strchr(wall_chars, map[CURR][CURC-1]) == NULL)
				  curc -= 1;
			break;
		case 'j':
			if (strchr(wall_chars, map[CURR+1][CURC]) == NULL)
				curr += 1;
			break;
		case 'k':
			if (strchr(wall_chars, map[CURR-1][CURC]) == NULL)
				curr -= 1;
			break;
		case 'l':
			if (strchr(wall_chars, map[CURR][CURC+1]) == NULL)
				curc += 1;
			break;
		default:
			break;
		}
		object_mov(1, MKSPOS(curr, curc));
		curs_mov(MKSPOS(curr, curc));
		paintscreen();

		if (map[CURR][CURC] == goal) {
			won = 1;
			break;
		}
	}

	object_del(1);
	if (won) {
		clearscreen();
		curs_mov(MKSPOS(getwinrows()/2, getwincols()/2 - 5));
		buf_putstr("You WIN! Yay!");
		curs_mov(MKSPOS(getwinrows()/2 + 1, getwincols()/2 - 25));
		char msgaux[70];
		sprintf(msgaux, "But you took %ld seconds... Can you do better?", time(NULL) - starttime);
		buf_putstr(msgaux);
		strcpy(msgaux, "(Press any key to exit)");
		curs_mov(MKSPOS(getwinrows()/2 + 2, getwincols()/2 - 12));
		buf_putstr(msgaux);
		paintscreen();
		scankey();
	}
	obj_grid_deinit();
	libascii_exit();
	free(wall_chars);
}
