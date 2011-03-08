/* Filename: engine.c
 * Authors: Chris Sims	(add your name here as you edit)
 * Date created: 24 Feb 2011
 * Description: Processing functions for zzzzzzzzzzzz
 */

#include "engine.h"
#include "defs.h"

void alarm_trigger(int signal) {
	update_status_bar();
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

void init_status_bar() {
	status_win = create_newwin(STATUS_ROWS, STATUS_COLS, 23, 0);
	status_panel = new_panel(status_win);
 	update_panels();
	doupdate();
}

void update_status_bar() {
	static int count = 0;
	count++;
	if (count == 4) {
		game.time++;
		count = 0;
		if (game.score <= MAX_TIME_SCORE) {
			game.score++;
		}
	}
	wmove(status_win, 0,0);
	wprintw(status_win, "Time elapsed: %d Current score: %d Lives: %d" ,\
						game.time, game.score, game.lives);
	wrefresh(status_win);
}

void init_pause_menu() {
	int max_x, max_y, starty, startx;

	getmaxyx(stdscr, max_y, max_x);

 	starty = (max_y - PAUSE_ROWS) / 2;
 	startx = (max_x - PAUSE_COLS) / 2;

 	pause_win = create_newwin(PAUSE_ROWS, PAUSE_COLS, starty, startx);
 	box(pause_win, 0 , 0);		/* 0, 0 gives default characters
					 			* for the vertical and horizontal
					 			* lines			*/
 	wmove(pause_win, 2,4);
 	wprintw(pause_win, "ZZZZZZZZZZZZ:Murder!");
 	wmove(pause_win, 9, 7);
 	wprintw(pause_win, "Paused");
 	wmove(pause_win, 10,4);
 	wprintw(pause_win, "Hit p to continue.");
 	pause_panel = new_panel(pause_win);
 	update_panels();
	doupdate();
	getch();
}

void toggle_pause_menu() {
	char input;
	if (!pause_win) {
		init_pause_menu();
	}
	if (game.paused) {
		hide_panel(pause_panel);
		update_panels();
		doupdate();
		set_ticker(INTERVAL);
		game.paused = false;
	}
	else if (!game.paused) {
		set_ticker(0);
		show_panel(pause_panel);
		update_panels();
		doupdate();
		game.paused = true;
		do {
			input = getch();
		} while (input != 'p');
		toggle_pause_menu();
	}
}

void move_character(int keypress) {
	switch (keypress) {
		case 'f':		//used to ensure that we fall with gravity
			blank_character();
			if (game.gravity == NORMAL) {
				if (check_spot(game.current_row - 1, game.current_column)) {
					game.current_row--;
				}
			}
			else {
				if (check_spot(game.current_row + 1, game.current_column)) {
					game.current_row++;
				}
			}
			disp_player();
			break;

		case KEY_LEFT:
			blank_character();
			if (check_spot(game.current_row, game.current_column - 1))
				game.current_column--;
			disp_player();
			break;

		case KEY_RIGHT:
			blank_character();
			if (check_spot(game.current_row, game.current_column + 1))
				game.current_column++;
			disp_player();
			break;

		case 'z':
			if (map.attribute[map.world_row]\
					[map.world_col]\
					[game.current_row + 1]\
					[game.current_column] == 'b') {
				blank_character();
				toggle_gravity();
				disp_player();
			}
			else if (map.attribute[map.world_row]\
					[map.world_col]\
					[game.current_row - 1]\
					[game.current_column] == 'b') {
				blank_character();
				toggle_gravity();
				disp_player();
			}
			break;

		case 'p': // hide the menu/intro and show the game
			toggle_pause_menu();
			break;
/*		case 'h':
			toggle_high_score_display();
			break;
		case 'm':
			toggle_game_menu();
			break; */
		case 'q':
			quit_game();
			break;
	}
}

bool check_spot(int row, int col) {
	switch (map.attribute[map.world_row]\
						[map.world_col]\
						[row][col]) {
		case BLOCKED:		//stop falling
			return false;
			break;
		case EMPTY:		//falling through space....
			return true;
			break;
		case DEADLY:
			//you_died();
			if(game.lives != 0)
			{
				blank_character();
				game.current_row = game.resurect_row;
				game.current_column = game.resurect_col;
				disp_player();
				game.lives--;
			}
			else
			{
				you_died();
			}
			break;
		case GRAVITYBAR_HORZ:
			blank_character();
			toggle_gravity();
			disp_player();
			return false;
			break;
		case GRAVITYBAR_VERT:
			blank_character();
			toggle_gravity();
			disp_player();
			return false;
			break;
		case GOAL:
			game.score += GOAL_PTS;
			//To prevent from getting infinite points, erase goal block
			map.attribute[map.world_row]\
						[map.world_col]\
						[row][col] = '*';
			return true;
			break;
		case WIN:
			game.score += GOAL_PTS;
			you_won();
			break;
		case UP:
			map.world_row--;
			game.current_row = 23;
			print_map();
			game.resurect_row = game.current_row - 1;
			game.resurect_col = game.current_column;
			return true;
			break;
		case DOWN:
			map.world_row++;
			game.current_row = 0;
			print_map();
			game.resurect_row = game.current_row + 1;
			game.resurect_col = game.current_column;
			return true;
			break;
		case RIGHT:
			map.world_col++;
			game.current_column = 0;
			print_map();
			game.resurect_row = game.current_row;
			game.resurect_col = game.current_column;
			return true;
			break;
		case LEFT:
			map.world_col--;
			game.current_column = 78;
			print_map();
			game.resurect_row = game.current_row;
			game.resurect_col = game.current_column;
			return true;
			break;
	}
	//Shouldn't ever get here...Added to remove compiler warning
	return false;	
}

void disp_player() {
	wattron(play_win, COLOR_PAIR(3));
	wmove(play_win, game.current_row, game.current_column);
	if (game.gravity == NORMAL) {
		waddch(play_win, PLAYER_NORM);
	}
	else {
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
	
	wrefresh(local_win);		/* Show that box 		*/

	return local_win;
}

void toggle_gravity() {
	if (game.gravity == NORMAL)
		game.gravity = REVERSE;
	else
		game.gravity = NORMAL;
}

void you_died() {
	wmove(play_win, 10,20);
	wprintw(play_win, "You died. Try not to hit the spikes.");
	wmove(play_win, game.max_rows, game.max_cols);
	wrefresh(play_win);
	sleep(1);
	wgetch(play_win);
	quit_game();
}
void you_won() {
	game.score += GOAL_PTS;
	wmove(play_win, 10,20);
	wprintw(play_win, "Congrats, you won!");
	wmove(play_win, game.max_rows, game.max_cols);
	wrefresh(play_win);
	sleep(1);
	wgetch(play_win);
	quit_game();
}

void quit_game() {
	process_high_score(game.score);
	del_panel(play_panel);
	del_panel(status_panel);
	del_panel(pause_panel);
	del_panel(gmenu_panel);
	delwin(play_win);
	delwin(status_win);
	delwin(pause_win);
	delwin(gmenu_win);
	endwin();
	puts("Thanks for playing!");
	exit(0);
}

