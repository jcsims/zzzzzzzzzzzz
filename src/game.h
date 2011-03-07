/* Filename: game.h
 * Authors: Chris Sims	(add your name here as you edit)
 * Date created: 18 Feb 2011
 * Description: Various definitions and prototypes for zzzzzzzzzzzz 
 */

#ifndef GAME_H_
#define GAME_H_

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <signal.h>
#include <panel.h>
#include <menu.h>
#include "map.h"
#include "engine.h"
#include "defs.h"

#define README "../data/README"

static void init_game ();
static void play_game();
static int init_alarm_handler();
static void show_game_menu();
static void clear_game_menu();
static void show_readme();
static void view_high_scores();
static void quit_no_play();
static void dealloc_menu();

#endif // GAME_H_
