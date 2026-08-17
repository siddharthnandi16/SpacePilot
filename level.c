#include <pdcurses.h>
#include <stdlib.h>
#include "gamedata.h"
#include "level.h"
#include "spawn.h"
#include "sound.h"
#include "dialogue.h"
#include "enemy.h"
extern int unsigned long tick;
float density = 0.2;
extern int max_x, max_y;
//Currently unimplemented functions to draw a background with a given density
char bgchar(int max_x, int max_y){
    const char chars[] = ".,'$^*()";
    int n = sizeof(chars) - 1;
    return chars[rand() % n];
}

bool should_draw_cell(int max_y, int max_x){
    return (rand() / (double)RAND_MAX) < density;
}
//Scrolls the game and renders the player. Also returns the number of rows scrolled
int scrollanddraw(int rows_scrolled){
    int unsigned long tick=0;
    tick++;
    static int old_px = -1, old_py = -1;

    // Erase the player's previous position before anything else moves
    if (old_px != -1) {
        mvaddch(old_py, old_px, ' ');
        rows_scrolled++;
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
    return rows_scrolled;
}

//Data for level 1
Level_Data level_1={
.spawn_table = spawn_table_1,
    .spawn_count = 1,          //Should be equal to number of entries in corresponding spawn_table
    .sound_table = sound_table_1,
    .sound_count = 0,          
    .dialogue_table = dialogue_table_1,
    .dialogue_count = 0
};
//Function that handles level progression (enemy spawning, sound, dialogue)
void level(int rows_scrolled, const Level_Data *level){
    for (int i = 0; i < level->spawn_count; i++) {
        if (level->spawn_table[i].fired) continue; // Skips entries that are already fired
        switch (level->spawn_table[i].trigger) {
            case TICK:
                if (tick >= level->spawn_table[i].trigger_time) {
                    spawn_enemy(level->spawn_table[i].type, level->spawn_table[i].behavior,
                                level->spawn_table[i].px, level->spawn_table[i].py,
                                level->spawn_table[i].strafe);
                    level->spawn_table[i].fired = true;
                }
                break;
            case ROW:
                if (rows_scrolled >= level->spawn_table[i].trigger_time) {
                    spawn_enemy(level->spawn_table[i].type, level->spawn_table[i].behavior,
                                level->spawn_table[i].px, level->spawn_table[i].py,
                                level->spawn_table[i].strafe);
                    level->spawn_table[i].fired = true;
                }
                break;
        }
    }
    // TBA: music and dialogue passes, same structure
}
