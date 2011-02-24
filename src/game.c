/* Filename: game.c
 * Authors: Chris Sims	(add your name here as you edit)
 * Date created: 18 Feb 2011
 * Description: Main loop file for zzzzzzzzzzzz
 */

#include "game.h"

int main (int argc, char *argv[]) {

	d_game_state newgame;
	d_game_map newmap;
	int test_char;

	init_game(&newgame, &newmap);
	display_intro(&newgame);
	print_map(&newmap);
	disp_player(&newmap, &newgame);

	while(true) {
		test_char = getch();
		move_character(test_char, &newmap, &newgame);
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
 	newgame->gravity = NORMAL;			//Start right-side up
 	newgame->current_row = STARTING_ROW;
	newgame->current_column = STARTING_COLUMN;

	init_pair(1, COLOR_RED, COLOR_BLACK);		//Red danger blocks, with black background
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);	//goal block
	init_pair(3, COLOR_GREEN, COLOR_BLACK);		//player character
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
