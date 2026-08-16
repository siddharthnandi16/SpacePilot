#include <pdcurses.h>
#include <stdlib.h>
#include "gamedata.h"
#include "level.h"

float density = 0.2;
extern int max_x, max_y;

char bgchar(int max_x, int max_y){
    const char chars[] = ".,'";
    int n = sizeof(chars) - 1;
    return chars[rand() % n];
}

bool should_draw_cell(int max_y, int max_x){
    return (rand() / (double)RAND_MAX) < density;
}

int scrollanddraw(void){
    int unsigned long tick=0;
    tick++;
    static int old_px = -1, old_py = -1;

    // Erase the player's previous position before anything else moves
    if (old_px != -1) {
        mvaddch(old_py, old_px, ' ');
    }

    scrollok(stdscr, TRUE);
    if (tick % 5 == 0){
    wscrl(stdscr, -1);
    }
    // Draw the player at its current position, on top of whatever's there
    attron(COLOR_PAIR(1));
    mvaddch((int)player.py, (int)player.px, player.symbol);
    attroff(COLOR_PAIR(1));
    old_px = (int)player.px;
    old_py = (int)player.py;

    refresh();
    return 1;
}