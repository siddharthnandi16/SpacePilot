#include <pdcurses.h>
#include <stdlib.h>
#include "player.h"
#define SCROLL_DELAY_MS 50  // lower = faster scroll
float density=0.2 //Higher= greater density of background
int max_x, max_y;
getmaxyx(stdscr, max_y, max_x);
int background_start_row = 0, background_end_row=0;
//Function to create a background with random chars. Filled with small chars
char bgchar(int max_x, int max_y){
seed = max_x + max_y;
srand(seed);
const char chars[] = ".,'"
int n = sizeof(chars) - 1;
    return chars[rand() % n];
}
//Decide how many cells should be drawn based on density
bool should_draw_cell(int max_y, int max_x){
    seed = max_x + max_y;
srand(seed);
return (rand() / (double)RAND_MAX) < density;
}

//This function automatically initalises the screen, scrolls upward and renders objects as they come into view
//It also calls the function to render the screen background
void scrollanddraw(int max_x, int max_y){
int rows_scrolled=0;
while(1){
    player.x = max_x/2, player.y = max_y/2;
    mvaddch(player.py,player.px,player.symbol);
    scrollok(stdscr, TRUE);
wscrl(stdscr, -1);    
    rows_scrolled++;
refresh();
}
}

