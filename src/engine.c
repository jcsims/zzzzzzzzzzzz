/* Filename: engine.c
 * Authors: Chris Sims	(add your name here as you edit)
 * Date created: 24 Feb 2011
 * Description: Processing functions for zzzzzzzzzzzz
 */

#include "engine.h"
#include "defs.h"

void alarm_trigger(int signal) {
	move_character( (int) 'f');
}

int set_ticker( int n_msecs ){
        struct itimerval new_timeset;
        long    n_sec, n_usecs;

        n_sec = n_msecs / 1000 ;		/* int part	*/
        n_usecs = ( n_msecs % 1000 ) * 1000L ;	/* remainder	*/
        new_timeset.it_interval.tv_sec  = n_sec;        /* set reload       */
        new_timeset.it_interval.tv_usec = n_usecs;      /* new ticker value */
        new_timeset.it_value.tv_sec     = n_sec  ;      /* store this       */
        new_timeset.it_value.tv_usec    = n_usecs ;     /* and this         */

	return setitimer(ITIMER_REAL, &new_timeset, NULL);
}

void move_character(int keypress) {
	switch (keypress) {
		case 'f':		//used to ensure that we fall with gravity
			blank_character();
			disp_player();
			break;

		case KEY_LEFT:
			blank_character();
			if (map.attribute[game.current_row][game.current_column - 1] == 'g')
				you_won();
			if (map.attribute[game.current_row][game.current_column - 1] != 'b')
				game.current_column--;
			disp_player();
			break;

		case KEY_RIGHT:
			blank_character();
			if (map.attribute[game.current_row][game.current_column + 1] == 'g')
				you_won();
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
			game.paused = true;
			set_ticker(0);
			hide_panel(play_panel);
			show_panel(intro_panel);
			update_panels();
			doupdate();
			break;

		case 'p': // hide the menu/intro and show the game
			game.paused = false;
			set_ticker(INTERVAL);
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
	wmove(play_win, game.max_rows - 1, game.max_cols - 1);
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
	if (!local_win)
		printw("Error allocating new window");
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
	wmove(play_win, 10,20);
	wprintw(play_win, "You died. Try not to hit the spikes.");
	wrefresh(play_win);
	sleep(1);
	wgetch(play_win);
	quit_game();
}
void you_won() {
	clear();
	wmove(play_win, 10,20);
	wprintw(play_win, "Congrats, you won!");
	wrefresh(play_win);
	sleep(1);
	wgetch(play_win);
	quit_game();
}



//TODO: Deallocate windows and panels on quit!
void quit_game() {
	process_high_score(201); //this score will need to be eventually replaced with w/e score variable we setup
	endwin();
	puts("Thanks for playing!");
	exit(0);
}

