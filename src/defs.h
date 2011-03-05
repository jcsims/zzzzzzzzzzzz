/* Filename: defs.h
 * Authors: Chris Sims	(add your name here as you edit)
 * Date created: 26 Feb 2011
 * Description: Header for zzzzzzzzzzzz.  Used for defines needed in
 * multiple files.
 */

#ifndef DEFS_H_
#define DEFS_H_

#define NORMAL true	//used for the character being right side up
#define REVERSE false	//or upside down
#define STARTING_ROW 1
#define STARTING_COLUMN 73
#define PLAYER_NORM 'M'
#define PLAYER_REVERSE 'W'
//Window sizes
#define PLAY_ROWS 23
#define PLAY_COLS 80
#define MENU_ROWS 18
#define MENU_COLS 30
#define PAUSE_ROWS 15
#define PAUSE_COLS 30
#define STATUS_ROWS 1
#define STATUS_COLS 80
//msecs
#define INTERVAL 250
//Score values
#define INIT_SCORE 0
#define MAX_TIME_SCORE 5000
#define GOAL_PTS 5000

//Map attributes
#define GRAVITYBAR_HORZ '-'
#define GRAVITYBAR_VERT '|'
#define DEADLY 'd'
#define BLOCKED 'b'
#define GOAL 'g'
#define WIN 'w'
#define UP 'u'
#define DOWN 'e'
#define LEFT 'l'
#define RIGHT 'r'
#define EMPTY '*'
#define START_WORLD_ROW 0
#define START_WORLD_COL 0

typedef struct d_game_state {
	bool paused;
	bool game_complete;
	int gravity;
	int current_row;
	int current_column;
	int max_rows;
	int max_cols;
	int time;
	int score;
} d_game_state;

typedef struct d_game_map {
	int world_row;
	int world_col;
	char attribute[2][3][24][80];
} d_game_map;

#endif //DEFS_H_
