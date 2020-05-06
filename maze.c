#include <stdio.h>
#include <time.h>
#include <errno.h>
#include "api.h"

#define CURR curr-1 /* because screen is 1-indexed but the array is 0-indexed */
#define CURC curc-1 /* ditto */

char map[200][200];
char scan;
short int curr = 6, curc = 6;

int main(int argc, char **argv)
{
	if (argc != 2) {
		printf("Please pass the map filename as the first and only argument.\n");
		exit(1);
	}
	FILE *dahmap = fopen(argv[1], "r");
	perror("Opening map file");
	if (errno != 0)
		exit(2);

	libascii_init();
	time_t starttime = time(NULL);
	int won = 0;

	object_create('@', MKSPOS(curr, curc));
	char t = '\0';
	int i = 0;
	int j = 0;
	while (t != EOF) {
		t = fgetc(dahmap);
		if (t == '\n') {
			i++;
			j = 0;
			continue;
		}
		map[i][j] = t;
		j++;
	}
	fclose(dahmap);

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
                                if (map[CURR][CURC-1] != '+')
					  curc -= 1;
				  break;
			case 'j':
                                  if (map[CURR+1][CURC] != '+')
					  curr += 1;
				  break;
			case 'k':
                                  if (map[CURR-1][CURC] != '+')
					  curr -= 1;
				  break;
			case 'l':
                                  if (map[CURR][CURC+1] != '+')
					  curc += 1;
				  break;
			default:
				  break;
		}
		object_mov(1, MKSPOS(curr, curc));
		curs_mov(MKSPOS(curr, curc));
		paintscreen();

		if (map[CURR][CURC] == '#') {
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
	paintscreen();
	libascii_exit();
}
