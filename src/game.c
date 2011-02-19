/* Filename: game.c
 * Authors: Chris Sims	(add your name here as you edit)
 * Date created: 18 Feb 2011
 * Description: Main game engine source file for zzzzzzzzzzzz 
 */


#include "game.h"

int main (int argc, char *argv[]) {

	d_game_state newgame;

	initscr(); 				//Start ncurses
	keypad(stdscr, true); 	//enable use of the arrow keys

	if (!init_game(&newgame)) {
		puts("Error: not able to init new game.")
		exit(1);
	}

	puts("Hello, game file reporting.");
	
	return 0;
}
