#include <pdcurses.h>
#include <stdbool.h>
#include <math.h>
//This function handles WASD inputs to move the player and can toggle player speed
void move_player(float *px, float *py, float dy, float dx, int max_x, int max_y, bool speed_mode_fast, float vx, float vy, bool q_was_down){
nodelay(stdscr, TRUE);
float new_px=*px, new_py=*py; //Stores the new player movement values temporarily
char choice;
while(1){
choice = getch();

if (choice == 'q'&& !q_was_down){
    speed_mode_fast = !speed_mode_fast;}
q_was_down= !q_was_down;
if (speed_mode_fast == FALSE){
    dx = dx/2;
    dy = dy/2;
}
else {(dy=vy, dx=vx);}
switch(choice){
case 'w':
new_py = *py + dy;
break;
case 's':
new_py = *py -dy;
break;
case 'a':
new_px= *px - dx;
break;
case 'd':
new_px= *px + dx;
break;
}
new_px = fminf(fmaxf(new_px, 0), max_x);
new_py = fminf(fmaxf(new_py, 0), max_y);
*px = new_px;
*py = new_py;
napms(16);
break;
}
}
