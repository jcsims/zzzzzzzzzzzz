/* Filename: engine.h
 * Authors: Chris Sims	(add your name here as you edit)
 * Date created: 24 Feb 2011
 * Description: Header for engine.c
 */

#ifndef ENGINE_H_
#define ENGINE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/time.h>
#include <ncurses.h>
#include <panel.h>
#include <unistd.h>		//sleep()
#include "map.h"
#include "defs.h"
#include "high_score.h"

extern d_game_state game;
extern d_game_map map;
extern WINDOW *play_win, *intro_win;
extern PANEL *play_panel, *intro_panel;

void alarm_trigger(int signal);
int set_ticker(int n_msecs);
void move_character(int keypress);
void quit_game();
void toggle_gravity();
void you_died();
void you_won();
void disp_player();
void blank_character();
WINDOW *create_newwin(int height, int width, int starty, int startx);


/*Define the game character
  Normal:

  o
 /|\
 / \

 Reversed:
 \ /
 \|/
  o
 
 */
//const char player_normal[3][3] = { {' ','o',' '}, {'/','|','\\'}, {'/',' ','\\'} };
//const char player_reversed[3][3] = { {'\\',' ','/'}, {'\\','|','/'}, {' ','o',' '} };

#endif // ENGINE_H_
