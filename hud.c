#include <pdcurses.h>
#include "gamedata.h"
#include "window.h"
#include "projectile.h"
#include "hud.h"
#include <math.h>
#define HUD_HEIGHT 3 
#define HUD_WIDTH 102
WINDOW *hud_win = NULL;
//Function to initialise a globally accessible HUD
void init_hud(int offset_y, int offset_x)
{
    hud_win = newwin(HUD_HEIGHT, HUD_WIDTH,
                     offset_y - 3, offset_x - 1);
}
//Function to draw and update the HUD
void drawHUD(Player *player){
    init_hud(offset_y,offset_x);
wattron(hud_win,COLOR_PAIR(1));
box(hud_win,0,0);
wattroff(hud_win,COLOR_PAIR(1));
wattron(hud_win,COLOR_PAIR(6));
mvwprintw(hud_win,1,1, "Lives:");
mvwprintw(hud_win,1,7, "%d",player->lives);
mvwprintw(hud_win,1,9, "Score:");
mvwprintw(hud_win,1,16, "%d",player->score);
mvwprintw(hud_win,1,20, "Weapon:");
WeaponType *current_weapon = get_weapon_template(player->weapon_id);
char *weapon_name = current_weapon->display_name;
mvwprintw(hud_win,1,27, "%s", weapon_name);
mvwprintw(hud_win,1,47, "Speed:");
float speed = sqrt((player->dx*player->dx) + (player->dy*player->dy));
mvwprintw(hud_win,1,54,"%.3f", speed);
mvwprintw(hud_win,1,60, "m/s");
wattroff(hud_win,COLOR_PAIR(6));
wrefresh(hud_win);
}