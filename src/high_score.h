/* Filename: high_score.h
 * Authors: Chris Sims	(add your name here as you edit)
 * Date created: 18 Feb 2011
 * Description: Definitions and prototypes needed for high score read/write 
 */

#ifndef HIGH_SCORE_H_
#define HIGH_SCORE_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>
#include "engine.h"

#define HIGH_SCORE_PATH "../data/high_scores"

extern PANEL *play_panel;

typedef struct high_score
{
    char name[10][20];
    char score[10][20];
}high_score;

int init_score_struct();
int process_high_score();


#endif	// HIGH_SCORE_H_
