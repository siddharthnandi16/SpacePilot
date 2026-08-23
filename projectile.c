#include <pdcurses.h>
#include <math.h>
#include "gamedata.h"
#define MAX_PROJECTILES 2000
//Table for storing projectiles. The values here are placeholders than will be overwritten during gameplay
Projectile projectiles[MAX_PROJECTILES] = {
    [0] = {
.px = 0, .py = 0,
    .dx = 1, .dy = 1, .angle = 90,
    .symbol = '*',
    .width = 1, .height = 1,
    .age = 0, .strafe=0,
    .pierce = 1, .turn_rate=0,
    .type = BULLET, .state=SPENT,
     .color=3, .player_owned = FALSE
    }
};
/*Chart of symbols based on projectile type
Bullet = +
Laser = |
Bomb = O
Missile = ^
Plasma = *
EMP = -
Chain Lighting = ~
*/
//List of player weapon types. All player weapons are in lowercase
const WeaponType autopistol = {
    .cooldown_frames = 60, .number = 1, .angle= 90, .type= BULLET, .modes = NORMAL
,.weapon_id = AUTOPISTOL_ID
};
const WeaponType machinegun = {
    .cooldown_frames = 10, .number = 2, .angle= 90, .type= BULLET, .modes = NORMAL
    ,.weapon_id = MACHINEGUN_ID
};
const WeaponType laserrifle = {
    .cooldown_frames = 60, .number = 1, .angle= 90, .type= LASER, .modes = NORMAL
    ,.weapon_id = LASRIFLE_PLAYER_ID
};
const WeaponType bomblauncher = {
    .cooldown_frames = 60, .number = 1, .angle= 90, .type= BOMB, .modes = NORMAL
    ,.weapon_id = BOMB_PLAYER_ID
};
const WeaponType missilelauncher = {
    .cooldown_frames = 60, .number = 1, .angle= 90, .type= MISSILE, .modes = NORMAL
    ,.weapon_id = MISSILE_PLAYER_ID
};
const WeaponType plasmarifle = {
    .cooldown_frames = 60, .number = 1, .angle= 90, .type= PLASMA, .modes = NORMAL
    ,.weapon_id = PLASMARIFLE_PLAYER_ID
};
const WeaponType empbomb = {
    .cooldown_frames = 600, .number = 1, .angle= 90, .type= EMP, .modes = NORMAL
    ,.weapon_id = EMP_ID
};
const WeaponType lightning = {
    .cooldown_frames = 240, .number = 5, .angle= 90, .type= CHAINLIGHTNING, .modes = NORMAL
    ,.weapon_id = LIGHTNING_ID
};
const WeaponType shotgun = {
    .cooldown_frames = 75, .number = 5, .angle= 90, .type= BULLET, .modes = NORMAL
    ,.weapon_id = SHOTGUN_ID
};
const WeaponType lasercannon = {
    .cooldown_frames = 30, .number = 3, .angle= 90, .type= LASER, .modes = NORMAL
    ,.weapon_id = LASERCANNON_ID
};
const WeaponType plasmacannon = {
    .cooldown_frames = 90, .number = 5, .angle= 90, .type= PLASMA, .modes = NORMAL
    ,.weapon_id = PLASMACANNON_ID
};
//List of enemy weapon types. All enemy weapon types are capitalised
const WeaponType GRUNT_RIFLE = {
    .cooldown_frames = 90, .number = 1, .angle= 90, .type= BULLET, .modes = NORMAL
    ,.weapon_id = GRUNT_WEAPON_ID
};
const WeaponType RAPIDFIRE_RIFLE = {
    .cooldown_frames = 30, .number = 1, .angle= 90, .type= BULLET, .modes = NORMAL
    ,.weapon_id = RAPIDFIRE_RIFLE_ID
};
const WeaponType LASER_RIFLE_ENEMY = {
    .cooldown_frames = 180, .number = 1, .angle= 90, .type= LASER, .modes = NORMAL
    ,.weapon_id = LASER_RIFLE_ENEMY_ID
};
const WeaponType BOMB_ENEMY_WEAPON = {
    .cooldown_frames = 180, .number = 1, .angle= 90, .type= BOMB, .modes = NORMAL
    ,.weapon_id = BOMB_ENEMY_ID
};
const WeaponType HUNTER_RIFLE = {
    .cooldown_frames = 20, .number = 1, .angle= 90, .type= BULLET, .modes = NORMAL
    ,.weapon_id = HUNTER_RIFLE_ID
};
//Function to find a free slot in the enemy pool
int findfreeprojectileslot(void){
    for(int i=0; i < MAX_PROJECTILES; i++){
        if (projectiles[i].state == SPENT){
            return i;
        }
    }
    return -1;
}
//Finds the address of a weapon and returns it. 
//Add a new case each time a new weapon is made
    const WeaponType* get_weapon_template(WeaponID weapon_id) {
    switch (weapon_id) {
        case AUTOPISTOL_ID:          return &autopistol;
        case MACHINEGUN_ID:          return &machinegun;
        case LASRIFLE_PLAYER_ID:     return &laserrifle;
        case BOMB_PLAYER_ID:         return &bomblauncher;
        case PLASMARIFLE_PLAYER_ID:  return &plasmarifle;
        case MISSILE_PLAYER_ID:      return &missilelauncher;
        case EMP_ID:                 return &empbomb;
        case LIGHTNING_ID:           return &lightning;
        case SHOTGUN_ID:             return &shotgun;
        case LASERCANNON_ID:         return &lasercannon;
        case PLASMACANNON_ID:        return &plasmacannon;
        case GRUNT_WEAPON_ID:        return &GRUNT_RIFLE;
        case RAPIDFIRE_RIFLE_ID:     return &RAPIDFIRE_RIFLE;
        case LASER_RIFLE_ENEMY_ID:   return &LASER_RIFLE_ENEMY;
        case BOMB_ENEMY_ID:          return &BOMB_ENEMY_WEAPON;
        case HUNTER_RIFLE_ID:        return &HUNTER_RIFLE;
        default:                     return NULL;
    }
}
//Function that fires one projectile at a given angle, returns cooldown timer
void fire_weapon(const WeaponType *weapon, float px, float py, float angle, bool player_owned){
int slot = findfreeprojectileslot();
if (slot == -1){
    return; //Stops execution if there are no free projectile slots
}
projectiles[slot].state = NORMAL;
projectiles[slot].px = px;
projectiles[slot].py = py;
projectiles[slot].type = weapon->type;
projectiles[slot].angle = angle;
projectiles[slot].age = 0;
projectiles[slot].width = 1;
projectiles[slot].height = 1;
switch(projectiles[slot].type){
case BULLET:
projectiles[slot].symbol = '+';
projectiles[slot].pierce = 1;
projectiles[slot].strafe = 0;
projectiles[slot].turn_rate = 0;
projectiles[slot].dx = 0;
projectiles[slot].dy = -1; //Moves directly upward
break;
case LASER:
projectiles[slot].symbol = '|';
projectiles[slot].pierce = 100;
projectiles[slot].strafe = 0;
projectiles[slot].turn_rate = 0;
projectiles[slot].dx = 0;
projectiles[slot].dy = -100;
break;
case BOMB:
projectiles[slot].symbol = 'O';
projectiles[slot].pierce = 1;
projectiles[slot].strafe = 0;
projectiles[slot].turn_rate = 0;
projectiles[slot].dx = 0;
projectiles[slot].dy = -2;
break;
case MISSILE:
projectiles[slot].symbol = '^';
projectiles[slot].pierce = 3;
projectiles[slot].strafe = 0;
projectiles[slot].turn_rate = 5;
projectiles[slot].dx = 0;
projectiles[slot].dy = -2;
break;
case PLASMA:
projectiles[slot].symbol = '*';
projectiles[slot].pierce = 5;
projectiles[slot].strafe = 0;
projectiles[slot].turn_rate = 0;
projectiles[slot].dx = 0;
projectiles[slot].dy = -5;
break;
case EMP:
projectiles[slot].symbol = '-';
projectiles[slot].pierce = 100;
projectiles[slot].strafe = 0;
projectiles[slot].turn_rate = 0;
projectiles[slot].dx = 0;
projectiles[slot].dy = 0;
projectiles[slot].width = 1000;
projectiles[slot].height = 1000;
break;
case CHAINLIGHTNING:
projectiles[slot].symbol = '~';
projectiles[slot].pierce = 10;
projectiles[slot].strafe = 0;
projectiles[slot].turn_rate = 0;
projectiles[slot].dx = 10;
projectiles[slot].dy = -10;
break;
}
if (player_owned == TRUE){
    projectiles[slot].player_owned = TRUE;
    projectiles[slot].color = 4;
}
else {projectiles[slot].player_owned = FALSE;
    projectiles[slot].color = 3;}
}
// Function that moves and updates projectiles
void move_projectiles(Projectile *projectiles, int max_x, int max_y){
    for(int i = 0; i < MAX_PROJECTILES; i++){
        if (projectiles[i].pierce <= 0) {
projectiles[i].state = SPENT;
}
if (projectiles[i].state != NORMAL) {
            continue;
        }
projectiles[i].age++;

// Skip standard straight-line movement for special-case types (deferred)
if (projectiles[i].type == CHAINLIGHTNING || projectiles[i].type == EMP) {
continue; // TODO: special handling later
        }
if (projectiles[i].angle != 90) {
            float rad = projectiles[i].angle * (M_PI / 180.0f); // convert degrees to radians - confirm your angle units
            float speed = sqrtf(projectiles[i].dx * projectiles[i].dx +
                                 projectiles[i].dy * projectiles[i].dy); // derive speed from the default dx/dy magnitude - or pull from WeaponType if you add that field
            projectiles[i].dx = speed * cosf(rad);
            projectiles[i].dy = -speed * sinf(rad); // negative since up = decreasing py
        }
        if (projectiles[i].type == MISSILE && projectiles[i].turn_rate > 0) {
            float target_angle = atan2f(-(player.py - projectiles[i].py),
                                          (player.px - projectiles[i].px)); // check sign conventions against your angle system
            float current_angle = atan2f(-projectiles[i].dy, projectiles[i].dx);
            float diff = target_angle - current_angle;
            // TODO: normalize diff to [-pi, pi] and clamp to turn_rate before applying
            projectiles[i].angle = current_angle + diff; // placeholder - needs turn_rate clamping
        }

        projectiles[i].px += projectiles[i].dx;
        projectiles[i].py += projectiles[i].dy;
        if (projectiles[i].py < 0 || projectiles[i].py >= max_y ||
            projectiles[i].px < 0 || projectiles[i].px >= max_x) {
            projectiles[i].state = SPENT;
        }
    }
}
//Function that renders projectiles each frame
void render_projectiles(Projectile *projectiles){
for(int i=0; i < MAX_PROJECTILES; i++){
    if (projectiles[i].state == NORMAL){
    attron(COLOR_PAIR(projectiles[i].color));
     mvaddch(projectiles[i].py, projectiles[i].px, projectiles[i].symbol);
     attroff(COLOR_PAIR(projectiles[i].color));
     refresh();
    }
}
}
//Function that erases old positions of projectiles each frame and removes spent projectiles
void erase_projectiles(Projectile *projectiles){
    for(int i=0; i < MAX_PROJECTILES; i++){
        if (projectiles[i].state == NORMAL || projectiles[i].state == SPENT){  
    mvaddch(projectiles[i].py, projectiles[i].px, ' ');
     }
        }
    }
