/* Filename: game.c
 * Authors: Chris Sims	(add your name here as you edit)
 * Date created: 18 Feb 2011
 * Description: Main game engine source file for zzzzzzzzzzzz 
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <curses.h>
#include "map.h"
#include "game.h"

static int current_row, current_column, gravity;

int main (int argc, char *argv[]) {

	d_game_state newgame;
	d_game_map newmap;
	int test_char;

	init_game(&newgame, &newmap);
	disp_player();
	print_map(&newmap);

	while(true) {
		test_char = getch();
		move_character(test_char);
	}
	
	test_char = getch();

	quit_game();
	
	return 0;
}

void init_game (d_game_state *newgame, d_game_map *newmap) {
 	initscr(); 				//Start ncurses
 	start_color();			//Enable use of color
	keypad(stdscr, true); 	//enable use of the arrow keys
	cbreak();				//pass all keypresses, but control characters (like signals)
	noecho();				//don't echo the characters as the player types

	read_map(newmap);		//Read the map from the data file
 	newgame->paused = false;
 	newgame->game_complete = false;
 	gravity = NORMAL;			//Start right-side up
 	current_row = STARTING_ROW;
	current_column = STARTING_COLUMN;
}

void disp_player() {
	int i, j;
	move(current_row, current_column);
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			move(current_row + i, current_column + j);
			if (gravity == NORMAL){
				printw("%c", player_normal[i][j]);		
			}
			else {
				printw("%c", player_reversed[i][j]);
			}
		}
	}
	refresh();
}

void blank_character() {
	int i, j;
	move(current_row, current_column);
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			move(current_row + i, current_column + j);
			printw(" ");	
		}
	}
	refresh();
}

void move_character(int keypress) {
	switch (keypress) {
		case KEY_LEFT:
			blank_character();
			current_column--;
			disp_player();
			break;
		
		case KEY_RIGHT:
			blank_character();
			current_column++;
			disp_player();
			break;

		case 'z':
			blank_character();
			toggle_gravity();
			disp_player();
			break;
		
		case 'q':
			quit_game();
			break;
			
	}
}

void quit_game() {
	endwin();
	puts("Thanks for playing!");
	exit(0);
}

void toggle_gravity() {
	if (gravity == NORMAL)
		gravity = REVERSE;
	else
		gravity = NORMAL;
}
