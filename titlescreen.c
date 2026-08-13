#include <stdio.h>
#include <stdlib.h>
#include <pdcurses.h>
#include <string.h>
#include "titlescreen.h"
int drawTitleScreen(){
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

for (int i = 0; i < num_lines; i++) {
    attron(COLOR_PAIR(1)); // Contains black and green
    mvprintw(start_y + i, start_x, "%s", titlescreen[i]);
}
mvprintw(start_y + 12, start_x + 6, "Press any key to start the game");
attroff(COLOR_PAIR(1));
refresh();
char choice;
choice = getch();
 //More functionality TBA 
}
