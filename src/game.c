/* Filename: game.c
 * Authors: Chris Sims	(add your name here as you edit)
 * Date created: 18 Feb 2011
 * Description: Main loop file for zzzzzzzzzzzz
 */

#include "game.h"

d_game_state game;
d_game_map map;
WINDOW *play_win, *intro_win;
PANEL *play_panel, *intro_panel;

int main (int argc, char *argv[]) {

	init_game();
	display_intro();	// make function display a window on top of current window
	//hide_panel(intro_panel);
	play_win = create_newwin(PLAY_ROWS, PLAY_COLS, 0, 0);
	play_panel = new_panel(play_win);
 	update_panels();
	doupdate();
	show_panel(play_panel);
	print_map();
	disp_player();
	
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

	while(true) {
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

	read_map();		//Read the map from the data file
 	game.paused = false;
 	game.game_complete = false;
 	game.gravity = NORMAL;			//Start right-side up
 	game.current_row = STARTING_ROW;
	game.current_column = STARTING_COLUMN;

	init_pair(1, COLOR_RED, COLOR_BLACK);		//Red danger blocks, with black background
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);	//goal block
	init_pair(3, COLOR_GREEN, COLOR_BLACK);		//player character
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

 	int starty = (LINES - INTRO_COLS) / 2;
 	int startx = (COLS - INTRO_COLS) / 2;

 	intro_win = create_newwin(INTRO_ROWS, INTRO_COLS, starty, startx);
 	wprintw(intro_win, "Hello there!");
 	intro_panel = new_panel(intro_win);
 	update_panels();
	doupdate();
	getch();
 }
