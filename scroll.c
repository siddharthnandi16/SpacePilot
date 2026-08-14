#include <pdcurses.h>
#include <stdlib.h>
#include "player.h"
//This function automatically scrolls upward and renders objects as they come into view
//It also renders the background of the game using procedural generation
void scroll()

int rows_scrolled=0;
while(1){
    scrollok(stdscr, TRUE);
wscrl(stdscr, -1);    
    rows_scrolled++;

}

