#include <pdcurses.h>
#include  "gamedata.h"
#include "dialogue.h"
#include "level.h"
#include "window.h"
#include "hud.h"
#define DIALOGUE_HEIGHT 1   
#define DIALOGUE_WIDTH 102
dialogue_entry dialogue_table_1[MAX_DIALOGUE]={
    [0] ={
.trigger = ROW, .auto_scroll=TRUE, .bold = TRUE, .color = 2, 
.fired = FALSE, .trigger_time = 0, .text = "Placeholder",
    },
    [1] ={
.trigger = TICK, .auto_scroll=TRUE, .bold = TRUE, .color = 2, 
.fired = FALSE, .trigger_time = 0, .text = "Placeholder",
    }
};

/* WINDOW *dialogue_win = NULL;
void init_dialogue_window(int offset_y, int offset_x){
    fprintf(stderr, "newwin(%d, %d, %d, %d)\n",
    DIALOGUE_HEIGHT, DIALOGUE_WIDTH,
    offset_y + PLAYFIELD_H + 1, offset_x - 1);
    fprintf(stderr, "dialogue_win failed to create! offset_y=%d offset_x=%d\n", offset_y, offset_x);
    dialogue_win = newwin(DIALOGUE_HEIGHT, DIALOGUE_WIDTH,
                           offset_y + PLAYFIELD_H + 1, offset_x - 1);
} */
void update_dialogue(dialogue_entry *dialogue_table){

    for (int i = 0; i < MAX_DIALOGUE; i++){
        if (dialogue_table[i].fired == TRUE){
        continue; // Skips entries that are already fired
        }
        switch(dialogue_table[i].trigger){
            case ROW: 
            if (rows_scrolled >= dialogue_table[i].trigger_time){
                werase(hud_win);
                dialogue_table[i].fired = TRUE;
                mvwprintw(hud_win, 2, 0, 
                    "%s", dialogue_table[i].text);
                wrefresh(hud_win);
            }
            break;
            case TICK:
            if (tick >= dialogue_table[i].trigger_time){
                werase(hud_win);
                dialogue_table[i].fired = TRUE;
                mvwprintw(hud_win, 2, 0, 
                    "%s", dialogue_table[i].text);
                wrefresh(hud_win);
            }
            break;
        }
    }
}

