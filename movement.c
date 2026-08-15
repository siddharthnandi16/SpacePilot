#include <pdcurses.h>
#include <stdbool.h>
#include <math.h>
#include "movement.h"

void move_player(float *px, float *py, float dy, float dx, int max_x, int max_y, bool *speed_mode_fast, float vx, float vy, bool *q_was_down){
    nodelay(stdscr, TRUE);
    float new_px = *px, new_py = *py;
    int choice = getch();

    if (choice == 'q' && !(*q_was_down)) {
        *speed_mode_fast = !(*speed_mode_fast);
    }
    *q_was_down = (choice == 'q');

    if (*speed_mode_fast) {
        dx = vx;
        dy = vy;
    } else {
        dx = vx / 2;
        dy = vy / 2;
    }

    switch (choice) {
        case 'w': new_py = *py - dy; break;
        case 's': new_py = *py + dy; break;
        case 'a': new_px = *px - dx; break;
        case 'd': new_px = *px + dx; break;
        default: break; // Position unchanged on no input
    }

    new_px = fminf(fmaxf(new_px, 0), (float)max_x);
    new_py = fminf(fmaxf(new_py, 0), (float)max_y);
    *px = new_px;
    *py = new_py;
}