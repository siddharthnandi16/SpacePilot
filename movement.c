#include <pdcurses.h>
#include <stdbool.h>
#include <math.h>
#include "movement.h"
#include "window.h"
void move_player(float *px, float *py, float dy, float dx, int max_x, int max_y, bool *speed_mode_fast, float vx, float vy, bool *q_was_down){
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    float new_px = *px, new_py = *py;
    int choice = getch();
    new_px = fminf(fmaxf(new_px, 0), max_x - 1); // -1 since columns are 0-indexed
new_py = fminf(fmaxf(new_py, 0), max_y - 1);

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
        case KEY_RESIZE:
        resize_term(0, 0);
        syncConsoleBufferToWindow();
        break;
        default: break; // Position unchanged on no input
    }

    new_px = fminf(fmaxf(new_px, 0), (float)max_x-1);
    new_py = fminf(fmaxf(new_py, 0), (float)max_y-1);
    *px = new_px;
    *py = new_py;
}