/* Filename: game.c
 * Authors: Chris Sims	(add your name here as you edit)
 * Date created: 18 Feb 2011
 * Description: Main game engine source file for zzzzzzzzzzzz
 */

#include "map.h"
#include "game.h"

static int current_row, current_column, gravity;

WINDOW *play_win, *intro_win;
PANEL *play_panel, *intro_panel;

int main (int argc, char *argv[]) {

	d_game_state newgame;
	d_game_map newmap;
	int test_char;

	init_game(&newgame, &newmap);
	display_intro(&newgame); // make function display a window on top of current window

 	int starty = (LINES - PLAY_ROWS) / 2;
 	int startx = (COLS - PLAY_COLS) / 2;
 	play_win = create_newwin(PLAY_ROWS, PLAY_COLS, starty, startx);
 	print_map(&newmap);
	disp_player();

	play_panel = new_panel(play_win);
	update_panels();
	doupdate();
/*****************************************************/



	while(true) {
		test_char = getch();
		move_character(test_char);
		//print_map(&newmap);
	}
	
	test_char = getch();

	quit_game();
	
	return 0;
}

void init_game (d_game_state *newgame, d_game_map *newmap) {
 	initscr(); 				//Start ncurses
 	start_color();			//Enable use of color
	keypad(stdscr, true); 	//enable use of the arrow keys
	cbreak();				//pass all keypresses, but control characters (like signals)
	noecho();				//don't echo the characters as the player types
	curs_set(0);			//Hide the cursor

	read_map(newmap);		//Read the map from the data file
 	newgame->paused = false;
 	newgame->game_complete = false;
 	gravity = NORMAL;			//Start right-side up
 	current_row = STARTING_ROW;
	current_column = STARTING_COLUMN;

	init_pair(1, COLOR_RED, COLOR_BLACK);		//Red danger blocks, with black background
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);	//goal block
	init_pair(3, COLOR_GREEN, COLOR_BLACK);		//player character
}

/*
void disp_player() {
	int i, j;
	move(current_row, current_column);
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			move(current_row + i, current_column + j);
			if (gravity == NORMAL){
				printw("%c", player_normal[i][j]);		
			}
			else {
				printw("%c", player_reversed[i][j]);
			}
		}
	}
	refresh();
}
*/

void disp_player() {
	wmove(play_win, current_row, current_column);
	wattron(play_win, COLOR_PAIR(3));
	if (gravity == NORMAL)
		waddch(play_win, PLAYER_NORM);
	else
		waddch(play_win, PLAYER_REVERSE);
	wattroff(play_win, COLOR_PAIR(1));
	wrefresh(play_win);
}

/*
void blank_character() {
	int i, j;
	move(current_row, current_column);
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			move(current_row + i, current_column + j);
			printw(" ");	
		}
	}
	refresh();
}
*/

void blank_character() {
	wmove(play_win, current_row, current_column);
	waddch(play_win, ' ');
	wrefresh(play_win);
}

void move_character(int keypress) {
	switch (keypress) {
		case KEY_LEFT:
			blank_character();
			current_column--;
			disp_player();
			break;
		
		case KEY_RIGHT:
			blank_character();
			current_column++;
			disp_player();
			break;

		case 'z':
			blank_character();
			toggle_gravity();
			disp_player();
			break;
		case 'm': // pause game and go to mentu/intro panel
			hide_panel(play_panel);
			show_panel(intro_panel);
			update_panels();
			doupdate();
			break;
		case 'p': // hide the menu/intro and show the game
			hide_panel(intro_panel);
			show_panel(play_panel);
			update_panels();
			doupdate();
			break;			
		case 'q':
			quit_game();
			break;
			
	}
}

void quit_game() {
	endwin();
	puts("Thanks for playing!");
	exit(0);
}

void toggle_gravity() {
	if (gravity == NORMAL)
		gravity = REVERSE;
	else
		gravity = NORMAL;
}

void display_intro (d_game_state *newgame) {

 	int starty = (LINES - INTRO_COLS) / 2;
 	int startx = (COLS - INTRO_COLS) / 2;

 	intro_win = create_newwin(INTRO_ROWS, INTRO_COLS, starty, startx);
 	wprintw(intro_win, "Hello there!");
	intro_panel = new_panel(intro_win);
	update_panels();
	doupdate();
 	getch();
 }

WINDOW *create_newwin(int height, int width, int starty, int startx) {
	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);		/* 0, 0 gives default characters
					 			* for the vertical and horizontal
					 			* lines			*/
	wrefresh(local_win);		/* Show that box 		*/

	return local_win;
}
