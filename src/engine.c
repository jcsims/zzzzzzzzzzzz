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
		case 'f':		//used to ensure that we fall with gravity
			blank_character();
			disp_player();
			break;

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

void disp_player() {
	wattron(play_win, COLOR_PAIR(3));
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
		wmove(play_win, game.current_row, game.current_column);
		waddch(play_win,PLAYER_NORM);
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
		wmove(play_win, game.current_row, game.current_column);
		waddch(play_win, PLAYER_REVERSE);
	}
	wattroff(play_win, COLOR_PAIR(3));
	wrefresh(play_win);
}

void blank_character() {
	wmove(play_win, game.current_row, game.current_column);
	waddch(play_win, ' ');
	wrefresh(play_win);
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
