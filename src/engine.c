/* Filename: engine.c
 * Authors: Chris Sims	(add your name here as you edit)
 * Date created: 24 Feb 2011
 * Description: Processing functions for zzzzzzzzzzzz
 */

#include "engine.h"

void alarm_trigger(int signal) {
	move_character( (int) 'f');
}

void move_character(int keypress) {
	switch (keypress) {
		case KEY_LEFT:
			blank_character();
			if (map.attribute[game.current_row][game.current_column - 1] != 'b')
				game.current_column--;
			disp_player();
			break;
		
		case KEY_RIGHT:
			blank_character();
			if (map.attribute[game.current_row][game.current_column + 1] != 'b')
				game.current_column++;
			disp_player();
			break;

		case 'z':
			if (map.attribute[game.current_row + 1][game.current_column] == 'b') {
				blank_character();
				toggle_gravity();
				disp_player();
			}
			else if (map.attribute[game.current_row - 1][game.current_column] == 'b') {
				blank_character();
				toggle_gravity();
				disp_player();
			}
			break;
		
		case 'q':
			quit_game();
			break;
			
		case 'f':		//used to ensure that we fall with gravity
			blank_character();
			disp_player();
			break;
	}
}

void disp_player() {
	attron(COLOR_PAIR(3));
	if (game.gravity == NORMAL) {
		switch(map.attribute[game.current_row - 1][game.current_column]) {
			case 'b':		//stop falling
				break;
			case '*':		//falling through space....
				game.current_row--;
				break;
			case 'd':
				you_died();
				break;
			case 'g':
				you_won();
				break;
		}
		move(game.current_row, game.current_column);
		addch(PLAYER_NORM);
	}
	else {
		switch(map.attribute[game.current_row + 1][game.current_column]) {
			case 'b':		//stop falling
				break;
			case '*':		//falling through space....
				game.current_row++;
				break;
			case 'd':
				you_died();
				break;
			case 'g':
				you_won();
				break;
		}
		move(game.current_row, game.current_column);
		addch(PLAYER_REVERSE);
	}
	attroff(COLOR_PAIR(3));
	refresh();
}

void blank_character() {
	move(game.current_row, game.current_column);
	addch(' ');
	refresh();
}

void display_intro (d_game_state *newgame) {
 	WINDOW *intro_win;
 	int starty = (LINES - INTRO_COLS) / 2;
 	int startx = (COLS - INTRO_COLS) / 2;

 	intro_win = create_newwin(INTRO_ROWS, INTRO_COLS, starty, startx);
 	wprintw(intro_win, "Hello there!");
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

void toggle_gravity() {
	if (game.gravity == NORMAL)
		game.gravity = REVERSE;
	else
		game.gravity = NORMAL;
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

void you_died() {
	clear();
	move(10,20);
	printw("You died. Try not to hit the spikes.");
	getch();
	quit_game();
}
void you_won() {
	clear();
	move(10,20);
	printw("Congrats, you won!");
	getch();
	quit_game();
}


void quit_game() {
	endwin();
	puts("Thanks for playing!");
	exit(0);
}

