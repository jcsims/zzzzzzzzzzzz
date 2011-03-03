/* Filename: game.c
 * Authors: Chris Sims (add your name here as you edit)
 *			S.Monette
 * Date created: 18 Feb 2011
 * Description: Main loop file for zzzzzzzzzzzz
 *	Edits:
 *		26Feb2011 - added (init_pair 4) for the entry/exit portals 'e'
 */

#include "game.h"

d_game_state game;
d_game_map map;
WINDOW *play_win, *intro_win, *status_win, *pause_win;
PANEL *play_panel, *intro_panel, *status_panel, *pause_panel;

int main (int argc, char *argv[]) {

	init_game();
	display_intro();	// make function display a window on top of current window
	play_win = create_newwin(game.max_rows, game.max_cols, 0, 0);
	play_panel = new_panel(play_win);
 	update_panels();
	doupdate();
	print_map();
	disp_player();
	init_status_bar();
	
	//update_panels();
	//doupdate();

	if (init_alarm_handler()) {
		perror("alarm handler");
		exit(1);
	}
	if (set_ticker(INTERVAL)) {
		perror("Set interval timer");
		exit(1);
	}

	while(true) {	//Main game loop
		move_character(getch());
	}
	
	getch();
	quit_game();
	
	return 0;
}

static void init_game () {
	

 	initscr(); 				//Start ncurses
 	start_color();			//Enable use of color
	keypad(stdscr, true); 	//enable use of the arrow keys
	cbreak();				//pass all keypresses, but control characters (like signals)
	noecho();				//don't echo the characters as the player types
	curs_set(0);			//Hide the cursor

	game.paused = false;
 	game.game_complete = false;
 	game.gravity = REVERSE;			//Start right-side up
 	game.current_row = STARTING_ROW;
	game.current_column = STARTING_COLUMN;
	game.max_rows = PLAY_ROWS;
	game.max_cols = PLAY_COLS;
	game.time = 0;
	game.score = INIT_SCORE;
	read_maps();		//Read the map from the data files
	map.world_row = START_WORLD_ROW;
	map.world_col = START_WORLD_COL;


	init_pair(1, COLOR_RED, COLOR_BLACK);		//Red danger blocks, with black background
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);	//goal block
	init_pair(3, COLOR_GREEN, COLOR_BLACK);		//player character
	init_pair(4, COLOR_BLACK, COLOR_BLACK);		//entry/exit portals 'e' on the maps
}

static int init_alarm_handler() {
	struct sigaction handler;
	sigset_t blocked;

	handler.sa_handler = alarm_trigger;		//trigger function to call move_character
	handler.sa_flags = 0;			//Don't need any options

	//Block SIGINT
	sigemptyset(&blocked);
	sigaddset(&blocked, SIGINT);

	handler.sa_mask = blocked;

	return sigaction (SIGALRM, &handler, NULL);
}

static void display_intro () {
	int max_x, max_y, starty, startx;

	getmaxyx(stdscr, max_y, max_x);

 	starty = (max_y - INTRO_ROWS) / 2;
 	startx = (max_x - INTRO_COLS) / 2;

 	intro_win = create_newwin(INTRO_ROWS, INTRO_COLS, starty, startx);
 	box(intro_win, 0 , 0);		/* 0, 0 gives default characters
					 			* for the vertical and horizontal
					 			* lines			*/
 	wmove(intro_win, 2,4);
 	wprintw(intro_win, "ZZZZZZZZZZZZ:Murder!");
 	wmove(intro_win, 10,4);
 	wprintw(intro_win, "Hit any key to play.");
 	intro_panel = new_panel(intro_win);
 	update_panels();
	doupdate();
	getch();
 }
