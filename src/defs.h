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
#define STARTING_ROW 10
#define STARTING_COLUMN 40
#define PLAYER_NORM '&'
#define PLAYER_REVERSE '?'
//Window sizes
#define PLAY_ROWS 23
#define PLAY_COLS 80
#define INTRO_ROWS 15
#define INTRO_COLS 30
#define PAUSE_ROWS 15
#define PAUSE_COLS 30
#define STATUS_ROWS 1
#define STATUS_COLS 80
//msecs
#define INTERVAL 250
//Score values
#define INIT_SCORE 5000
#define GOAL_PTS 5000

//Map attributes
#define DEADLY 'd'
#define BLOCKED 'b'
#define GOAL 'g'
#define EGRESS 'e'
#define MAP_PATH "../data/map02"
//#define MAP_PATH "../data/map"

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
	char visible[24][80];
	char attribute[24][80];
} d_game_map;

#endif //DEFS_H_