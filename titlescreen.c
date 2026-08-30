#include <stdio.h>
#include <stdlib.h>
#include <pdcurses.h>
#include <string.h>
#include "miniaudio.h"
#include "titlescreen.h"
#include "gamedata.h"
#include "sound.h"
#include "window.h"
#define NUM_CHAR_OPTIONS (sizeof(char_options) / sizeof(char_options[0]))
GameMode drawTitleScreen(void){ 
   PlaySoundEffect(&loaded_sounds[Titlescreen_MUSIC]);
    const char *menu_options[] = {
    "Story Mode",
    "Endless Mode",
    "High Scores",
    "Music Room",
    "Quit"
};
 #define NUM_MENU_OPTIONS (sizeof(menu_options) / sizeof(menu_options[0]))
    erase();
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    const char *titlescreen[] = {
    " _____                       ______ _ _       _   ",
    "/  ___|                      | ___ (_) |     | |  ",
    "\\ `--. _ __   __ _  ___ ___  | |_/ /_| | ___ | |_ ",
    " `--. \\ '_ \\ / _` |/ __/ _ \\ |  __/| | |/ _ \\| __|",
    "/\\__/ / |_) | (_| | (_|  __/ | |   | | | (_) | |_ ",
    "\\____/| .__/ \\__,_|\\___\\___| \\_|   |_|_|\\___/ \\__|",
    "      | |                                         ",
    "      |_|                                         "
};
int num_lines=8;
int max_x, max_y;
getmaxyx(stdscr, max_y, max_x);
int art_width = strlen(titlescreen[0]); // All lines are of same width, used to make it centred
int start_y = PLAYFIELD_H / 4;                // Prints the title screen near the top
int start_x = (PLAYFIELD_W - art_width) / 2;


//mvprintw(start_y + 12, start_x + 6, "Press any key to start the game");
int selected = 0;
int game_starting = 0; //1= true, 0=false
keypad(stdscr, TRUE);

while(1) {
    nodelay(stdscr, TRUE);
    handle_mute_toggle();
    erase();  // Clear screen each frame
    
 for (int i = 0; i < num_lines; i++) {
    attron(COLOR_PAIR(1)); // Contains black background and green foreground
    mvprintw(offset_y + i, offset_x + start_x, "%s", titlescreen[i]);
}
    // Draw menu options
    int menu_y = offset_y + 12;
    for (int i = 0; i < NUM_MENU_OPTIONS; i++) {
        if (i == selected) {
            attron(A_REVERSE);
        }
        mvprintw(menu_y + i, offset_x + start_x, "%s", menu_options[i]);
        if (i == selected) {
            attroff(A_REVERSE);
        }
    }
    refresh();
    
    int ch = getch();
    switch(ch) {
        case KEY_RESIZE:
        erase();
        resize_term(0, 0);
        getmaxyx(stdscr, max_y, max_x);
        update_playfield_offset(max_x, max_y);
        refresh();
        syncConsoleBufferToWindow();
        break;
        case 60419:  // Up
            selected = (selected - 1 + NUM_MENU_OPTIONS) % NUM_MENU_OPTIONS;
            break;
        case 60418:  // Down
            selected = (selected + 1) % NUM_MENU_OPTIONS;
            break;
        case '\n':  // Press enter to confirm selection
        ma_sound_stop(&loaded_sounds[Titlescreen_MUSIC]);
        game_starting = 1;
            return (GameMode)selected;
        default:
            break;
    }
    if (game_starting == 1){
        break;
    }
}
napms(8);
return (GameMode)selected;
 //More functionality TBA 
}
const char *char_options[] = {
    "Fighter Jet",
    "Flying Fortress",
    "Experimental Fighter",
    "Debug Player"
};

void Draw_Char_Select(Player *player){
    int character_selected = 0; //1 for true, 0 for false
    nodelay(stdscr, FALSE);
    erase();
    int char_selected = 0;
    int ch, max_x, max_y;
    while(1){
 for (int i = 0; i < NUM_CHAR_OPTIONS; i++) {
        if (i == char_selected) {
            attron(A_REVERSE);
        }
        mvprintw(offset_y + i, offset_x + PLAYFIELD_W/3, "%s", char_options[i]);
        if (i == char_selected) {
            attroff(A_REVERSE);
        }
    }
    refresh();
    ch = getch();
    switch(ch) {
        case KEY_RESIZE:
        erase();
        resize_term(0, 0);
        getmaxyx(stdscr, max_y, max_x);
        update_playfield_offset(max_x, max_y);
        refresh();
        syncConsoleBufferToWindow();
        break;
        case 60419:  // Up
            char_selected = (char_selected - 1 + NUM_CHAR_OPTIONS) % NUM_CHAR_OPTIONS;
            break;
        case 60418:  // Down
            char_selected = (char_selected + 1) % NUM_CHAR_OPTIONS;
            break;
        case '\n':  // Press enter to confirm selection
        character_selected = 1;
        default:
        break;
    }
     if (character_selected == 1){
        nodelay(stdscr, TRUE);
    switch(char_selected){
        case 0: //Fighter jet
        *player = fighter_jet;
        break;
        case 1: //Flying fortress
        *player = flying_fortress;
        break;
        case 2: //Experimental fighter
        *player = experimental_fighter;
        break;
        case 3: //Debug
        break;
        default:
        break;
    }
    erase();
     break;
    }
    }
    napms(8);
}