/* Filename: map.c
 * Authors: Chris Sims (add your name here as you edit)
			T.Burmeister
			S.Monette
 * Date created: 17 Feb 2011
 * Edits:
		24 Feb 2011 - maping now drawn in window using w[ncursefunc](play_win, [ncurses func attributes])
		26Feb2011 - add case 'e' to print_map() to draw egress portals
 * Description: read in and process the map data file, making populating the
 * map elements of the game data structure passed to it.
 */

#include "map.h"


int read_map() {
	
	FILE *inFile;
    char scanned;
    int map_row, map_column;

	// open input file for reading
	if (!(inFile = fopen(MAP_PATH, "r"))) {
		perror("Couldn't open map file.");
		return 1;
	}

	for (map_row = 0; map_row < game.max_rows; map_row++) {
		for (map_column = 0; map_column < game.max_cols; map_column++) {
			scanned = fgetc(inFile);
			if (scanned != '\n')
		        map.attribute[map_row][map_column] = scanned;
		    else
		    	map.attribute[map_row][map_column] = 'b';
		}
	}
    fclose(inFile);

    return 0;
} 

int print_map() {
	int map_row, map_column;

	for (map_row = 0; map_row < game.max_rows; map_row++) {
		for (map_column = 0; map_column < game.max_cols; map_column++) {
			wmove(play_win, map_row, map_column);
			switch (map.attribute[map_row][map_column]) {
				case '*':		//this will be most of the space, so save some comparison
					waddch(play_win,' ');
					break;
				case 'b':
					wattron(play_win, A_STANDOUT);
					waddch(play_win, ' ');
					wattroff(play_win, A_STANDOUT);
					break;
				case 'd':
					wattron(play_win, A_BLINK | COLOR_PAIR(1));
					waddch(play_win, '^');
					wattroff(play_win, A_BLINK | COLOR_PAIR(1));
					break;
				case 'g':
					wattron(play_win, COLOR_PAIR(2));
					waddch(play_win, '@');
					wattroff(play_win, COLOR_PAIR(2));
					break;
				case 'e':
					wattron(play_win, COLOR_PAIR(4));
					waddch(play_win, 'e');
					wattroff(play_win, COLOR_PAIR(4));
					break;
			}
		}
	}
	update_panels();
	doupdate();
	return 0;
}
