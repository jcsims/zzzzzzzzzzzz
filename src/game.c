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

int main (int argc, char *argv[]) {

	d_game_state newgame;

	init_game(&newgame);

	printw("Paused? %d  Game finished? %d\n", newgame.paused, newgame.game_complete);
	getch();

	endwin();
	
	return 0;
}

void init_game (d_game_state *newgame) {
 	initscr(); 				//Start ncurses
	keypad(stdscr, true); 	//enable use of the arrow keys
	raw();					//pass all keypresses, including control characters

 	newgame->paused = false;
 	newgame->game_complete = false;
}
