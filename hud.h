#ifndef HUD_H
#define HUD_H
void drawHUD(Player *player);
void init_hud(int offset_y, int offset_x);
extern WINDOW *hud_win;
#endif