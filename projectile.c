#include <pdcurses.h>
#include "gamedata.h"
#define MAX_PROJECTILES 2000
//Table for storing projectiles. The values here are placeholders than will be overwritten during gameplay
Projectile projectiles[MAX_PROJECTILES] = {
    [0] = {
.px = 0, .py = 0,
    .dx = 1, .dy = 1,
    .symbol = '%',
    .width = 1, .height = 1,
    .age = 0, .strafe=0,
    .pierce = 1, .turn_rate=1,
    .type = BULLET, .state=NORMAL
    }
};
//
static const WeaponType rapid_pistol = {
    .cooldown_frames = 60, .number = 1, .angle= 90, .type= BULLET, .modes = NORMAL
};
