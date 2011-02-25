/* Filename: game.c
 * Authors: Chris Sims	(add your name here as you edit)
 * Date created: 18 Feb 2011
 * Description: Main loop file for zzzzzzzzzzzz
 */

#include "game.h"

d_game_state game;
d_game_map map;


int main (int argc, char *argv[]) {

	
	int test_char;

	init_game();
	display_intro();
	print_map();
	disp_player();
	if (init_alarm_handler()) {
		perror("alarm handler");
		exit(1);
	}
	if (set_ticker(INTERVAL)) {
		perror("Set interval timer");
		exit(1);
	}

	while(true) {
		test_char = getch();
		move_character(test_char);
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
