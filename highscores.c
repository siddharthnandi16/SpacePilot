#include <string.h>
#include <stdio.h>
#include <pdcurses.h>
#include "gamedata.h"
#include "highscores.h"
#include "window.h"
#define NAME_MAX_LEN 50
//Helper function for to get the player's class name
const char *get_class_name(enum PlayerClass class) {
    switch (class) {
        case PLAYER_FIGHTER:      return "Fighter Jet";
        case PLAYER_FORTRESS:     return "Flying Fortress";
        case PLAYER_EXPERIMENTAL: return "Experimental Fighter";
        default:                  return "Unknown";
    }
}
//Stores high scores in a file
void Write_high_scores(Player *player){
    erase();
    FILE *score_file_story = fopen("High_Scores_Story.txt", "a");
    FILE *score_file_endless = fopen("High_Scores_Endless.txt", "a");
    if (score_file_endless == NULL || score_file_story == NULL){
        fprintf(stderr, "Unable to access score record files!");
    return;
    }
    mvprintw(offset_y + PLAYFIELD_H/3 , offset_x + PLAYFIELD_W/3, "Enter high scores?(y/n)");
    char score_choice = 'a';
    while(score_choice != 'y' && score_choice != 'n'){
        scrollok(stdscr, FALSE);
        nodelay(stdscr, FALSE);
    score_choice = getch();
    if (score_choice == 'y'){
        const char *player_class = get_class_name(player->class);
        char player_name[NAME_MAX_LEN] = "BLANK";
        mvprintw(offset_y + PLAYFIELD_H/3 + 2 , offset_x + PLAYFIELD_W/3, "Enter your name.");
        wgetnstr(stdscr, player_name, NAME_MAX_LEN);
        scrollok(stdscr, TRUE);
        nodelay(stdscr, TRUE);
    if(game_mode == LEVEL_SELECT || game_mode == STORY_MODE){
        fprintf(score_file_story, "Name: %s Score: %d Class: %s\n", player_name, player->score, player_class);
    }
    else if(game_mode == ENDLESS_MODE){
       fprintf(score_file_endless, "Name: %s Score: %d Class: %s\n", player_name, player->score, player_class);
    }
    }
    if(score_choice == 'n'){
        scrollok(stdscr, TRUE);
        nodelay(stdscr, TRUE);
    mvprintw(offset_y + PLAYFIELD_H/3 + 2 , offset_x + PLAYFIELD_W/3, "Score not saved.");
    }
    }
fclose(score_file_story);
fclose(score_file_endless);
}
