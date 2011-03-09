/* Filename: map.h
 * Authors: Chris Sims	(add your name here as you edit)
 *			S.Monette
 * Date created: 17 Feb 2011
 * Description: Various definitiions and function prototypes used in map.c
 *	Edits:
 *		26Feb2011 - add #define EGRESS 'e' attribute for entry/exit 
					portals on maps
					change #define MAP_PATH from map to map02 
 *
 */

/* Definitions to make the code readable: easy to change row and column 
 * numbers, as well as chars that will represent various attributes of
 * the spots on the map. 
 * Blocked: game character cannot occupy the spot
 * Deadly: game character will die when occupying this spot
 * Goal: player wins the game when occupying this spot
 * Egress: transition to another map area
 */

#ifndef MAP_H_
#define MAP_H_

#include <curses.h>
#include <panel.h>
#include "engine.h"
#include "defs.h"

#define MAP0 "../data/map00"
#define MAP1 "../data/map01"
#define MAP2 "../data/map02"
#define MAP3 "../data/map03"
#define MAP4 "../data/map04"
#define MAP5 "../data/map05"

/* World Map
+----+----+----+
| 00 | 01 | 02 |
+----+----+----+
| 03 | 04 | 05 |
+----+----+----+
*/

extern d_game_state game;
extern d_game_map map;
extern WINDOW *play_win, *status_win;
extern PANEL *play_panel, *status_panel;

int read_maps();
int print_map();

#endif	// MAP_H_
