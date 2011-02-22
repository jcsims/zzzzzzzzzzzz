/* Filename: map.c
 * Authors: Chris Sims	(add your name here as you edit)
 * Date created: 17 Feb 2011
 * Description: read in and process the map data file, making populating the
 * map elements of the game data structure passed to it.
 */

#include <stdio.h>
#include "map.h"

int read_map(d_game_map *map) {
	
	FILE *inFile;
    char scanned;
    int map_row, map_column;

	// open input file for reading
	if (!(inFile = fopen(MAP_PATH, "r"))) {
		perror("Couldn't open map file.");
		return 1;
	}

	for (map_row = 0; map_row < 24; map_row++) {
		for (map_column = 0; map_column < 80; map_column++) {
			scanned = fgetc(inFile);
			if (scanned != '\n')
		        map->attribute[map_row][map_column] = scanned;
		    else
		    	map->attribute[map_row][map_column] = 'b';
		}
	}
    fclose(inFile);

    return 0;
} 

int print_map(d_game_map *map) {
	int map_row, map_column;

	for (map_row = 0; map_row < 24; map_row++) {
		for (map_column = 0; map_column < 80; map_column++) {
			move(map_row, map_column);
			switch (map->attribute[map_row][map_column]) {
				case '*':		//this will be most of the space, so save some comparison
					addch(' ');
					break;
				case 'b':
					attron(A_STANDOUT);
					addch(' ');
					attroff(A_STANDOUT);
					break;
				case 'd':
					attron(A_BLINK | COLOR_PAIR(1));
					addch('^');
					attroff(A_BLINK | COLOR_PAIR(1));
					break;
				case 'g':
					attron(COLOR_PAIR(2));
					addch('@');
					attroff(COLOR_PAIR(2));
					break;
			}
		}
	}
	refresh();
	return 0;
}
