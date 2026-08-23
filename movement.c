#include <pdcurses.h>
#include <stdbool.h>
#include <math.h>
#include <windows.h>
#include "movement.h"
#include "window.h"
#include "projectile.h"
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
        case KEY_UP: new_py = *py - dy; break;
        case KEY_DOWN: new_py = *py + dy; break;
        case KEY_LEFT: new_px = *px - dx; break;
        case KEY_RIGHT: new_px = *px + dx; break;
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
//Function that fires player weapons
#define NUM_WEAPON_SLOTS 6
void fire_player(Player *player) {
    static bool switch_key_was_down[NUM_WEAPON_SLOTS] = {false};
    int slot_keys[NUM_WEAPON_SLOTS] = {'1', '2', '3', '4', '5', '6'};

    // Switches weapons once per click
    for (int i = 0; i < NUM_WEAPON_SLOTS; i++) {
        bool key_down = (GetAsyncKeyState(slot_keys[i]) & 0x8000) != 0;
        if (key_down && !switch_key_was_down[i]) {
            if (player->inventory[i] != EMPTY_ID) {
                player->weapon_id = player->inventory[i];
            }
            // Does nothing if the slot is empty
        }
        switch_key_was_down[i] = key_down;
    }

    // Firing - held, gated by cooldown
    bool fire_key_down = (GetAsyncKeyState('Z') & 0x8000) != 0;
    if (fire_key_down) {
        player->fire_rate++;
        const WeaponType *weapon = get_weapon_template(player->weapon_id);
        if (weapon != NULL && player->fire_rate >= weapon->cooldown_frames) {
            fire_weapon(weapon, player->px, player->py - 1, 90, TRUE);
            player->fire_rate = 0;
        }
    }
}