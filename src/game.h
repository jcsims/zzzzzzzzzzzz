/* Filename: game.h
 * Authors: Chris Sims	(add your name here as you edit)
 * Date created: 18 Feb 2011
 * Description: Various definitions and prototypes for zzzzzzzzzzzz 
 */

#include <stdio.h>
#include <stdbool.h>

typedef struct d_game_state {
	bool paused;
	bool game_complete;
} d_game_state;

void init_game (d_game_state *newgame);