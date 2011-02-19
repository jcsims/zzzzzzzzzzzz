/* Filename: game.h
 * Authors: Chris Sims	(add your name here as you edit)
 * Date created: 18 Feb 2011
 * Description: Various definitions and prototypes for zzzzzzzzzzzz 
 */

#include <stdio.h>
#include <stdbool.h>
#include <ncurses.h>
#include "maps.h"

typedef struct d_game_state {
	bool paused;
	bool game_complete;
}

int init_game (d_game_state *newgame) {
 	newgame->paused = false;
 	newgame->game_complete = false;
}
