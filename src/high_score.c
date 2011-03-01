/* Filename: high_score.c
 * Authors: Chris Sims	(add your name here as you edit)
 * Date created: 18 Feb 2011
 * Description: Read in and save the game high score info 
 */

 //TODO: Make sure to block interrupts while writing and reading the file

#include "high_score.h"

WINDOW *high_score_win;

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

int check_score(high_score *temp, int tmpint)
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
            return 1;
        }
    }
    return 1;
}

int write_high_score(high_score *temp)
{
    FILE *fout;
    int i;

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

    fclose(fout);

    return 1;
}

void create_hs_win(char name[20])
{
	high_score_win = create_newwin(PLAY_ROWS, PLAY_COLS, 0, 0);

	wmove(high_score_win, 2, 25);
	wprintw(high_score_win, "Congrats you got a high score!!!");
	wmove(high_score_win, 3, 25);
	wprintw(high_score_win, "Plese enter your first name: ");
	wrefresh(high_score_win);
	set_ticker(0);
	echo();
	mvgetstr(3, 54, name);
}


int process_high_score(int score)
{
    high_score list;
    init_score_struct(&list);
    check_score(&list, score);
    write_high_score(&list);

    return 1;
}
