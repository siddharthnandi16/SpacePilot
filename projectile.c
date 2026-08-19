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
//List of basic weapon types
static const WeaponType autopistol = {
    .cooldown_frames = 60, .number = 1, .angle= 90, .type= BULLET, .modes = NORMAL
};
static const WeaponType machinegun = {
    .cooldown_frames = 10, .number = 2, .angle= 90, .type= BULLET, .modes = NORMAL
};
static const WeaponType laserrifle = {
    .cooldown_frames = 60, .number = 1, .angle= 90, .type= LASER, .modes = NORMAL
};
static const WeaponType bomblauncher = {
    .cooldown_frames = 60, .number = 1, .angle= 90, .type= BOMB, .modes = NORMAL
};
static const WeaponType missilelauncher = {
    .cooldown_frames = 60, .number = 1, .angle= 90, .type= MISSILE, .modes = NORMAL
};
static const WeaponType plasmarifle = {
    .cooldown_frames = 60, .number = 1, .angle= 90, .type= PLASMA, .modes = NORMAL
};
static const WeaponType empbomb = {
    .cooldown_frames = 600, .number = 1, .angle= 90, .type= EMP, .modes = NORMAL
};
static const WeaponType lightning = {
    .cooldown_frames = 240, .number = 5, .angle= 90, .type= CHAINLIGHTNING, .modes = NORMAL
};
static const WeaponType shotgun = {
    .cooldown_frames = 75, .number = 5, .angle= 90, .type= BULLET, .modes = NORMAL
};
static const WeaponType lasercannon = {
    .cooldown_frames = 30, .number = 3, .angle= 90, .type= LASER, .modes = NORMAL
};