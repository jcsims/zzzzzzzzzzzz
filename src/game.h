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
#include "map.h"
#include "engine.h"
#include "defs.h"

static void init_game ();
static int init_alarm_handler();
static void display_intro ();

#endif // GAME_H_
