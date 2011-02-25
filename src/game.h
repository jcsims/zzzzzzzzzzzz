/* Filename: game.h
 * Authors: Chris Sims	(add your name here as you edit)
 * Date created: 18 Feb 2011
 * Description: Various definitions and prototypes for zzzzzzzzzzzz 
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <curses.h>
#include <panel.h>

#define NORMAL true	//used for the character being right side up
#define REVERSE false	//or upside down
#define STARTING_ROW 10
#define STARTING_COLUMN 40
#define PLAYER_NORM '&'
#define PLAYER_REVERSE '?'
#define INTRO_ROWS 10
#define INTRO_COLS 20
#define PLAY_ROWS 24
#define PLAY_COLS 80


typedef struct d_game_state {
	bool paused;
	bool game_complete;
} d_game_state;

void init_game (d_game_state *newgame, d_game_map *newmap);
void disp_player();
void blank_character();
void move_character(int keypress);
void quit_game();
void toggle_gravity();

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
