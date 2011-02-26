/* Filename: map.h
 * Authors: Chris Sims	(add your name here as you edit)
 *			S.Monette
 * Date created: 17 Feb 2011
 * Description: Various definitiions and function prototypes used in map.c
 *	Edits:
 *		26Feb2011 - add #define EGRESS 'e' attribute for entry/exit portals on maps
					change #define MAP_PATH from map to map02 
 *
 */

/* Definitions to make the code readable: easy to change row and column 
 * numbers, as well as chars that will represent various attributes of
 * the spots on the map. 
 * Blocked: game character cannot occupy the spot
 * Deadly: game character will die when occupying this spot
 * Goal: player wins the game when occupying this spot
 */

#ifndef MAP_H_
#define MAP_H_

#include <curses.h>
#include <panel.h>
 
#define ROWS 24
#define COLUMNS 80
//Map attributes
#define DEADLY 'd'
#define BLOCKED 'b'
#define GOAL 'g'
#define EGRESS 'e'
#define MAP_PATH "../data/map02"
//#define MAP_PATH "../data/map"



typedef struct d_game_map {
	char visible[24][80];
	char attribute[24][80];
} d_game_map;

extern d_game_map map;
extern WINDOW *play_win;
extern PANEL *play_panel;

int read_map();
int print_map();

#endif	// MAP_H_