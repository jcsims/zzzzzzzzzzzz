/* Filename: map.h
 * Authors: Chris Sims	(add your name here as you edit)
 * Date created: 17 Feb 2011
 * Description: Various definitiions and function prototypes used in map.c
 */

/* Definitions to make the code readable: easy to change row and column 
 * numbers, as well as chars that will repersent various qualities of
 * the spots on the map. 
 * Blocked: game character cannot occupy the spot
 * Deadly: game character will die when occupying this spot
 * Goal: player wins the game when occupying this spot
 */
 
 #define ROWS 24
 #define COLUMNS 80
 #define DEADLY d
 #define BLOCKED b
 #define GOAL g

 #define DATA_FILE ../data/map1

typedef struct d_game_map {
	char visible[ROWS][COLUMNS];
	char 
};