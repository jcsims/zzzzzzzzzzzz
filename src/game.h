/* Filename: game.h
 * Authors: Chris Sims	(add your name here as you edit)
 * Date created: 18 Feb 2011
 * Description: Various definitions and prototypes for zzzzzzzzzzzz 
 */

#ifndef GAME_H_
#define GAME_H_

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <sys/time.h>
#include "map.h"
#include "engine.h"

void init_game (d_game_state *newgame, d_game_map *newmap);
int set_ticker(int n_msecs);

#endif // GAME_H_