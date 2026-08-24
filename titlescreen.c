#include <stdio.h>
#include <stdlib.h>
#include <pdcurses.h>
#include <string.h>
#include "titlescreen.h"
#include "gamedata.h"
#define NUM_MENU_OPTIONS (sizeof(menu_options) / sizeof(menu_options[0]))
GameMode drawTitleScreen(void){
    const char *menu_options[] = {
    "Story Mode",
    "Endless Mode",
    "High Scores",
    "Music Room",
    "Quit"
};

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
int start_y = max_y / 4;                // Prints the title screen near the top
int start_x = (max_x - art_width) / 2;


//mvprintw(start_y + 12, start_x + 6, "Press any key to start the game");
int selected = 0;
int game_starting = 0; //1= true, 0=false
keypad(stdscr, TRUE);

while(1) {
    erase();  // Clear screen each frame
    
 for (int i = 0; i < num_lines; i++) {
    attron(COLOR_PAIR(1)); // Contains black background and green foreground
    mvprintw(start_y + i, start_x, "%s", titlescreen[i]);
}
    // Draw menu options
    int menu_y = start_y + 12;
    for (int i = 0; i < NUM_MENU_OPTIONS; i++) {
        if (i == selected) {
            attron(A_REVERSE);
        }
        mvprintw(menu_y + i, start_x, "%s", menu_options[i]);
        if (i == selected) {
            attroff(A_REVERSE);
        }
    }
    
    refresh();
    
    int ch = getch();
    switch(ch) {
        case 60419:  // Up
            selected = (selected - 1 + NUM_MENU_OPTIONS) % NUM_MENU_OPTIONS;
            break;
        case 60418:  // Down
            selected = (selected + 1) % NUM_MENU_OPTIONS;
            break;
        case '\n':  // Confirms selection
        game_starting = 1;
            return (GameMode)selected;
        default:
            break;
    }
    if (game_starting == 1){
        break;
    }
}

return (GameMode)selected;
 //More functionality TBA 
}
