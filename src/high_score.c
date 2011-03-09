/*
 Filename: high_score.c
 * Authors: Chris Sims	(add your name here as you edit)
 * Date created: 18 Feb 2011
 * Description: Read in and save the game high score info 
 */

 //TODO: Make sure to block interrupts while writing and reading the file

#include "high_score.h"

static int check_score();
static int write_high_score();
static void create_hs_win();

WINDOW *high_score_win;
//PANEL *high_score_panel;

int init_score_struct(high_score *temp)
{
    FILE *fin;
    int i;

    if(!(fin = fopen(HIGH_SCORE_PATH, "r")))
    {
        printf("Error opening high_scores.");
        return 0;
    }

    for(i = 0; i < 10; i++)
    {
        fscanf(fin, "%s", temp->name[i]);
        fscanf(fin, "%s", temp->score[i]);
    }

    fclose(fin);

    return 1;
}

static int check_score(high_score *temp, int tmpint)
{
    int i, j;
    char tmpname[20];
    char tmpscore[20];
    char tmpscore2[20];
    char tmpname2[20];
    char score[20];
    char name[20];

    for(i = 0; i < 10; i++)
    {
        if(tmpint > atoi(temp->score[i]))
        {
            create_hs_win(name);
			if(strcmp(name, ""))
			{
            	strcpy(tmpname, temp->name[i]);
            	strcpy(tmpscore, temp->score[i]);
            	strcpy(temp->name[i], name);
            	sprintf(score, "%d", tmpint);
            	strcpy(temp->score[i], score);

            	for(j = i+1; j < 10; j++)
            	{
                	strcpy(tmpname2 ,temp->name[j]);
                	strcpy(tmpscore2 ,temp->score[j]);
                	strcpy(temp->name[j], tmpname);
                	strcpy(temp->score[j], tmpscore);
                	strcpy(tmpname, tmpname2);
                	strcpy(tmpscore, tmpscore2);
            	}
			}
            return 1;
        }
    }
    return 1;
}

static int write_high_score(high_score *temp)
{
    FILE *fout;
    int i;
	sigset_t intmask;

	if((sigemptyset(&intmask) == -1) || (sigaddset(&intmask, SIGINT) == -1))
	{
		perror("Failed to initialize the signal mask");
		return 1;
	}
	sigprocmask(SIG_BLOCK, &intmask, NULL);
    if(!(fout = fopen(HIGH_SCORE_PATH, "w+")))
    {
        printf("Error opening high_scores.");
        return 0;
    }
    for(i = 0; i < 10; i++)
    {
        fprintf(fout, "%s ", temp->name[i]);
        fprintf(fout, "%s\n", temp->score[i]);
    }
	sigprocmask(SIG_UNBLOCK, &intmask, NULL);
    fclose(fout);
    return 1;
}

static void create_hs_win(char name[20])
{
	int start_x, start_y, max_x, max_y;
	
	getmaxyx(stdscr, max_y, max_x);
	start_y = (max_y - PLAY_ROWS) / 2;
	start_x = (max_x - PLAY_COLS) / 2;
   	hide_panel(play_panel);
    update_panels();
    doupdate();
	high_score_win = create_newwin(game.max_rows, game.max_cols, start_y, start_x);
//	high_score_panel = new_panel(high_score_win);
//	update_panels();
//	doupdate();
	wmove(high_score_win, 2, 25);
	wprintw(high_score_win, "Congrats you got a high score!!!");
	wmove(high_score_win, 3, 25);
	wprintw(high_score_win, "Please enter your first name: ");
	wrefresh(high_score_win);
	set_ticker(0);
	echo();
	mvgetstr(start_y + 3, start_x + 54, name);
	wrefresh(high_score_win);
}


int process_high_score(int score)
{
    high_score list;
    init_score_struct(&list);
    check_score(&list, score);
    write_high_score(&list);
	delwin(high_score_win);

    return 1;
}

