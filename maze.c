#include <stdio.h>
#include "api.h"

#define CURR curr-1 /* because screen is 1-indexed but the array is 0-indexed */
#define CURC curc-1 /* because screen is 1-indexed but the array is 0-indexed */

char map[200][200];
char scan;
short int curr = 6, curc = 6;

int main(void)
{
	libascii_init();
	object_create('@', MKSPOS(curr, curc));
	FILE *dahmap = fopen("map.txt", "r");
	{
		int i = 0;
		int j = 0;
		char t = '\0';
		for (;;) {
			t = fgetc(dahmap);
			if (t == EOF)
				break;
			if (t == '\n') {
				i++;
				j = 0;
				continue;
			}
			map[i][j] = t;
			j++;
		}
	}
	fclose(dahmap);

	for (int i = 0; i < getwinrows(); i++) {
		for (int j = 0; j < getwincols(); j++) {
			curs_mov(MKSPOS(i+1, j+1));
			buf_putstr(char2str(map[i][j]));
		}
	}
	paintscreen();

	while (scan != 'q') {
		scan = scankey();
		for (int i = 0; i < getwinrows(); i++) {
			for (int j = 0; j < getwincols(); j++) {
				curs_mov(MKSPOS(i+1, j+1));
				buf_putstr(char2str(map[i][j]));
			}
		}
		switch (scan) {
			case 'h':
                                if (map[CURR][CURC-1] != '+')
					  curc -= 1;
				  if (map[CURR][CURC-1] != '#')
					  goto won;
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
		paintscreen();
	}

won:
	object_del(1);
	libascii_exit();
}
