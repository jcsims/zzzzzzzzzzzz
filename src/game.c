/* Filename: game.c
 * Authors: Chris Sims (add your name here as you edit)
 *			S.Monette
 * Date created: 18 Feb 2011
 * Description: Main loop file for zzzzzzzzzzzz
 *	Edits:
 *		26Feb2011 - added (init_pair 4) for the entry/exit portals 'e'
 */

#include "game.h"

static void init_game ();
static void play_game();
static int init_alarm_handler();
static void show_game_menu();
static void clear_game_menu();
static void show_readme();
static void view_high_scores();
static void quit_no_play();
static void dealloc_menu();

d_game_state game;
d_game_map map;
WINDOW *play_win, *status_win, *pause_win, *gmenu_win;
PANEL *play_panel,  *status_panel, *pause_panel, *gmenu_panel;
static ITEM **my_items;
static MENU *my_menu;
static ITEM *cur_item;

int main (int argc, char *argv[]) {

	init_game();
	show_game_menu();
		
	return 0;
}

void init_game () {
	
 	initscr(); 				//Start ncurses
 	start_color();			//Enable use of color
	keypad(stdscr, true); 	//enable use of the arrow keys
	//pass all keypresses, but also control characters (like signals)
	cbreak();				
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
	game.lives = 5;
	game.resurect_gravity = REVERSE;
	game.resurect_row = 4;
	game.resurect_col = 2;
	game.timescore = INIT_SCORE;
	game.score = INIT_SCORE;
	read_maps();		//Read the map from the data files
	map.world_row = START_WORLD_ROW;
	map.world_col = START_WORLD_COL;

	//Red danger blocks, with black background
	init_pair(1, COLOR_RED, COLOR_BLACK);		
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);	//goal block
	init_pair(3, COLOR_GREEN, COLOR_BLACK);		//player character
	init_pair(4, COLOR_BLACK, COLOR_BLACK);		//entry/exit portals
	init_pair(5, COLOR_CYAN, COLOR_BLACK);		//reverse gravity bars

	if (init_alarm_handler()) {
		perror("alarm handler");
		exit(1);
	}
}

static void play_game() {
	int start_x, start_y, max_x, max_y;

	dealloc_menu();

	getmaxyx(stdscr, max_y, max_x);
    start_y = (max_y - PLAY_ROWS) / 2;
    start_x = (max_x - PLAY_COLS) / 2;

	play_win = create_newwin(game.max_rows, game.max_cols, start_y, start_x);
	play_panel = new_panel(play_win);
 	update_panels();
	doupdate();
	print_map();
	disp_player();
	init_status_bar();

	
	if (set_ticker(INTERVAL)) {
		perror("Set interval timer");
		exit(1);
	}

	while(true) {	//Main game loop
		move_character(getch());
	}
	
	getch();
	quit_game();
}

static int init_alarm_handler() {
	struct sigaction handler;
	sigset_t blocked;

	//trigger function to call move_character
	handler.sa_handler = alarm_trigger;		
	handler.sa_flags = 0;			//Don't need any options

	//Block SIGINT
	sigemptyset(&blocked);
	sigaddset(&blocked, SIGINT);

	handler.sa_mask = blocked;

	return sigaction (SIGALRM, &handler, NULL);
}

static void show_game_menu() {
    int max_x, 
    	max_y, 
    	starty, 
    	startx,
    	c,
    	n_choices,
    	i;

    char *menuChoices[] = {
	    "Play Game",
	    "View Readme",
	    "View High Scores",
	    "Quit",
	};

	void (*p)();

	getmaxyx(stdscr, max_y, max_x);
    starty = (max_y - MENU_ROWS) / 2;
    startx = (max_x - MENU_COLS) / 2;

    gmenu_win = create_newwin(MENU_ROWS, MENU_COLS, starty, startx);
 	gmenu_panel = new_panel(gmenu_win);

    n_choices = (sizeof(menuChoices) / sizeof(menuChoices[0]));
    my_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));
    //Initialize the menu items
    for (i = 0; i < n_choices; i++) {
    	my_items[i] = new_item(menuChoices[i], "");
    }
    //point them to the proper function
    set_item_userptr(my_items[0], play_game);
    set_item_userptr(my_items[1], show_readme);
    set_item_userptr(my_items[2], view_high_scores);
    set_item_userptr(my_items[3], quit_no_play);

    my_items[n_choices] = (ITEM *)NULL;

    my_menu = new_menu((ITEM **)my_items);
    //Associate our menu with the game window
    set_menu_win(my_menu, gmenu_win);
    set_menu_sub(my_menu, derwin(gmenu_win, MENU_ROWS - 6, MENU_COLS - 4, 5,3));
    clear_game_menu();
    post_menu(my_menu);
    
    while(true) {   
    	update_panels();
    	doupdate();
    	c = getch();
	    switch(c) {   
		    case KEY_DOWN:
                menu_driver(my_menu, REQ_DOWN_ITEM);
                break;
            case KEY_UP:
                menu_driver(my_menu, REQ_UP_ITEM);
                break;
            case 10: //Enter
            	cur_item = current_item(my_menu);
				p = item_userptr(cur_item);
				p();
				pos_menu_cursor(my_menu);
				break;
        }
    }
}

static void clear_game_menu() {
	werase(gmenu_win);
	box(gmenu_win, 0 , 0); 
	wmove(gmenu_win, 2,4);
 	wprintw(gmenu_win, "ZZZZZZZZZZZZ:Murder!");
}

static void show_readme() {
	FILE *readin;
	char readme[README_ROWS][README_COLS];
	int i;
	int curX = 4;
	int curY = 4;

	unpost_menu(my_menu);
	readin = fopen(README, "r");
	for(i = 0; i < README_ROWS; i++)
	{
		fgets(readme[i], README_COLS, readin);
	}
	fclose(readin);
	for(i = 0; i < README_ROWS; i++)
	{
		wmove(gmenu_win, curY + i, curX);
		wprintw(gmenu_win, readme[i]);
	}
	box(gmenu_win, 0, 0);
	update_panels();
	doupdate();
	getch();
	clear_game_menu();
	post_menu(my_menu);
}

static void view_high_scores() {
	high_score list;
    int i;
    int curX = 5;
    int curY = 5;

	unpost_menu(my_menu);
	wmove(gmenu_win, 3,5);
    wprintw(gmenu_win, "****High Scores****");
    wmove(gmenu_win, curY, curX); // 3 down, 5th col 
    init_score_struct(&list);
    for(i = 0; i<10;i++) {
        wprintw(gmenu_win, "%d)", i+1);
        wmove(gmenu_win, curY, curX + 3);
        wprintw(gmenu_win, "%s", list.name[i]);
        wmove(gmenu_win, curY, curX + 15);
        wprintw(gmenu_win, "%s", list.score[i]);
        curY++;
        wmove(gmenu_win, curY, curX);
    }
    update_panels();
    doupdate();
    getch();
    clear_game_menu();
    post_menu(my_menu);
}

static void quit_no_play() {
	dealloc_menu();
	del_panel(gmenu_panel);
	delwin(gmenu_win);
	endwin();
	exit(0);
}

static void dealloc_menu() {
	int i,
		n_items;

	n_items = sizeof(my_items)/sizeof(ITEM *);
	unpost_menu(my_menu);
	for (i = 0; i < n_items; i++) {
		free_item(my_items[i]);
	}
	free_menu(my_menu);
}
