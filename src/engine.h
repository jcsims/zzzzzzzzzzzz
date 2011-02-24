/* Filename: engine.h
 * Authors: Chris Sims	(add your name here as you edit)
 * Date created: 24 Feb 2011
 * Description: Header for engine.c
 */

#ifndef ENGINE_H_
#define ENGINE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <ncurses.h>
#include "map.h"


#define NORMAL true	//used for the character being right side up
#define REVERSE false	//or upside down
#define STARTING_ROW 10
#define STARTING_COLUMN 40
#define PLAYER_NORM '&'
#define PLAYER_REVERSE '?'
#define INTRO_ROWS 10
#define INTRO_COLS 20

typedef struct d_game_state {
	bool paused;
	bool game_complete;
	int gravity;
	int current_row;
	int current_column;
} d_game_state;


void move_character(int keypress, d_game_map *map, d_game_state *game);
void quit_game();
void toggle_gravity(d_game_state *game);
void you_died();
void you_won();
void disp_player(d_game_map *map, d_game_state *game);
void blank_character(d_game_state *game);
void display_intro (d_game_state *newgame);
WINDOW *create_newwin(int height, int width, int starty, int startx);


/*Define the game character
  Normal:

  o
 /|\
 / \

 Reversed:
 \ /
 \|/
  o
 
 */
//const char player_normal[3][3] = { {' ','o',' '}, {'/','|','\\'}, {'/',' ','\\'} };
//const char player_reversed[3][3] = { {'\\',' ','/'}, {'\\','|','/'}, {' ','o',' '} };

#endif // ENGINE_H_