#include <pdcurses.h>
#include <math.h>
#include "gamedata.h"
#include "window.h"
#define MAX_PROJECTILES 2000
#define MAX_ENEMIES 100
//Table for storing projectiles. The values here are placeholders than will be overwritten during gameplay
Projectile projectiles[MAX_PROJECTILES] = {
    [0] = {
.px = -1, .py = -1,
.old_px=-1, .old_py=-1,
    .dx = 0, .dy = 0, .angle = 90,
    .symbol = '*',
    .width = 1, .height = 1,
    .age = 0, .strafe=0,
    .pierce = 1, .turn_rate=0,
    .type = BULLET, .state=SPENT,
     .color=3, .player_owned = FALSE,
     .damage = 1
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
    .cooldown_frames = 15, .number = 1, .angle= 90, .type= BULLET, .modes = NORMAL
,.weapon_id = AUTOPISTOL_ID
};
const WeaponType machinegun = {
    .cooldown_frames = 5, .number = 2, .angle= 90, .type= BULLET, .modes = NORMAL
    ,.weapon_id = MACHINEGUN_ID
};
const WeaponType laserrifle = {
    .cooldown_frames = 20, .number = 1, .angle= 90, .type= LASER, .modes = NORMAL
    ,.weapon_id = LASRIFLE_PLAYER_ID
};
const WeaponType bomblauncher = {
    .cooldown_frames = 30, .number = 1, .angle= 90, .type= BOMB, .modes = NORMAL
    ,.weapon_id = BOMB_PLAYER_ID
};
const WeaponType missilelauncher = {
    .cooldown_frames = 20, .number = 1, .angle= 90, .type= MISSILE, .modes = NORMAL
    ,.weapon_id = MISSILE_PLAYER_ID
};
const WeaponType plasmarifle = {
    .cooldown_frames = 5, .number = 1, .angle= 90, .type= PLASMA, .modes = NORMAL
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
    .cooldown_frames = 40, .number = 5, .angle= 90, .type= BULLET, .modes = NORMAL
    ,.weapon_id = SHOTGUN_ID
};
const WeaponType lasercannon = {
    .cooldown_frames = 30, .number = 3, .angle= 90, .type= LASER, .modes = NORMAL
    ,.weapon_id = LASERCANNON_ID
};
const WeaponType plasmacannon = {
    .cooldown_frames = 10, .number = 5, .angle= 90, .type= PLASMA, .modes = NORMAL
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
            //Debug code
             //fprintf(stderr, "Found free slot: %d\n", i);
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
#define LASER_DURATION_FRAMES 150
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
projectiles[slot].damage = 1;
break;
case LASER:
projectiles[slot].symbol = '|';
projectiles[slot].pierce = 100;
projectiles[slot].strafe = 0;
projectiles[slot].turn_rate = 0;
projectiles[slot].dx = 0;
projectiles[slot].dy = 0;
projectiles[slot].damage = 3;
break;
case BOMB:
projectiles[slot].symbol = 'O';
projectiles[slot].pierce = 1;
projectiles[slot].strafe = 0;
projectiles[slot].turn_rate = 0;
projectiles[slot].dx = 0;
projectiles[slot].dy = -0.5;
projectiles[slot].damage = 3;
break;
case MISSILE:
projectiles[slot].symbol = '^';
projectiles[slot].pierce = 3;
projectiles[slot].strafe = 0;
projectiles[slot].turn_rate = 30; //Higher = more accurate
projectiles[slot].dx = 0;
projectiles[slot].dy = -2;
projectiles[slot].damage = 2;
break;
case PLASMA:
projectiles[slot].symbol = '*';
projectiles[slot].pierce = 5;
projectiles[slot].strafe = 0;
projectiles[slot].turn_rate = 0;
projectiles[slot].dx = 0;
projectiles[slot].dy = -3;
projectiles[slot].damage = 5;
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
projectiles[slot].damage = 0;
break;
case CHAINLIGHTNING:
projectiles[slot].symbol = '~';
projectiles[slot].pierce = 10;
projectiles[slot].strafe = 0;
projectiles[slot].turn_rate = 0;
projectiles[slot].dx = 10;
projectiles[slot].dy = -10;
projectiles[slot].damage = 3;
break;
}
if (player_owned == TRUE){
    projectiles[slot].player_owned = TRUE;
    projectiles[slot].color = 4;
}
else if (player_owned == FALSE){projectiles[slot].player_owned = FALSE;
    projectiles[slot].color = 3;}
}
// Function that moves and updates projectiles
void move_projectiles(Projectile *projectiles, int max_x, int max_y){
    for(int i = 0; i < MAX_PROJECTILES; i++){
        projectiles[i].old_px = projectiles[i].px;
        projectiles[i].old_py = projectiles[i].py;
        projectiles[i].age++; //Updates projectile age per tick
        if (projectiles[i].pierce <= 0) {
projectiles[i].state = SPENT;
}
if (projectiles[i].type == LASER) {
    if (projectiles[i].age >= LASER_DURATION_FRAMES) {
        projectiles[i].state = SPENT;
    }
    continue; // Skips normal movement
}
if(projectiles[i].type == BOMB && projectiles[i].age >= 15){
    projectiles[i].state = EXPLODING;
}
if (projectiles[i].state == EXPLODING){
    projectiles[i].state = SPENT;  
    int offset_angle = 90;
    for (int j= 0; j < 12; j++){
int slot_1 = findfreeprojectileslot();
//Debug code for checking if projectile slot finding function is working properly
//fprintf(stderr, "j=%d: got slot %d, its current state=%d\n", j, slot_1, projectiles[slot_1].state);
if (slot_1 == -1){
    offset_angle = offset_angle + 30;
    continue; //Skips execution if there are no free projectile slots
}
projectiles[slot_1].state = NORMAL;
//Debug code to check if slot is being set properly
//fprintf(stderr, "Set slot %d to NORMAL\n", slot_1);
projectiles[slot_1].player_owned = projectiles[i].player_owned;
projectiles[slot_1].px = projectiles[i].px ;
projectiles[slot_1].py = projectiles[i].py ;
projectiles[slot_1].type = BULLET;
projectiles[slot_1].angle = offset_angle;
projectiles[slot_1].symbol = '+';
projectiles[slot_1].pierce = 1;
projectiles[slot_1].strafe = 0;
projectiles[slot_1].turn_rate = 0;
projectiles[slot_1].dx = 0;
projectiles[slot_1].dy = -1; //Moves directly upward
projectiles[slot_1].damage = 1;
projectiles[slot_1].color = projectiles[i].color;
offset_angle = offset_angle + 30;
//Debug code for checking number of projectiles spawned
//fprintf(stderr, "Created shrapnel: slot %d, angle %d, initial dx=%.2f dy=%.2f\n", 
//       slot_1, offset_angle, projectiles[slot_1].dx, projectiles[slot_1].dy);
    }
    //Debug code for checking state of first three slots in pool
      //  fprintf(stderr, "After explosion: slot 0 state=%d, slot 1 state=%d, slot 2 state=%d\n", 
      //  projectiles[0].state, projectiles[1].state, projectiles[2].state);
}
//Skips check for projectiles that are inactive
if (projectiles[i].state != NORMAL) {
            continue;
        }
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
    float target_x, target_y;
    bool has_target = false;

    if (projectiles[i].player_owned) {
        // Player-owned missiles home in on the nearest living enemy
        float best_dist_sq = -1.0f;
        for (int e = 0; e < MAX_ENEMIES; e++) {
            if (enemies[e].state == ALIVE) {
                float dx = enemies[e].px - projectiles[i].px;
                float dy = enemies[e].py - projectiles[i].py;
                float dist_sq = dx * dx + dy * dy;
                if (best_dist_sq < 0 || dist_sq < best_dist_sq) {
                    best_dist_sq = dist_sq;
                    target_x = enemies[e].px;
                    target_y = enemies[e].py;
                    has_target = true;
                }
            }
        }
    } else {
        // Enemy-owned missiles home in on the player
        target_x = player.px;
        target_y = player.py;
        has_target = true;
    }

    if (has_target) {
        float target_angle_rad = atan2f(-(target_y - projectiles[i].py),
                                          (target_x - projectiles[i].px));
        float current_angle_rad = projectiles[i].angle * (M_PI / 180.0f);

        float diff = target_angle_rad - current_angle_rad;
        while (diff > M_PI)  diff -= 2.0f * M_PI;
        while (diff < -M_PI) diff += 2.0f * M_PI;

        float turn_rate_rad = projectiles[i].turn_rate * (M_PI / 180.0f);
        if (diff > turn_rate_rad)  diff = turn_rate_rad;
        if (diff < -turn_rate_rad) diff = -turn_rate_rad;

        float new_angle_rad = current_angle_rad + diff;
        projectiles[i].angle = new_angle_rad * (180.0f / M_PI);
    }
    // if no target found, missile continues straight at its current angle
}

        projectiles[i].px += projectiles[i].dx;
        projectiles[i].py += projectiles[i].dy;
        if (projectiles[i].py < 0 || projectiles[i].py >= PLAYFIELD_H ||
            projectiles[i].px < 0 || projectiles[i].px >= PLAYFIELD_W) {
            projectiles[i].state = SPENT;
        }
    }
}
//Function that calculates the bounds for laser-type projectiles
 float start_row =0 ,end_row = 0;
void get_laser_bounds(Projectile *proj, int max_y, int max_x, float *start_row, float *end_row){
    getmaxyx (stdscr, max_y, max_x);
if (proj->player_owned == TRUE){
    *start_row = (int)proj->py;
    *end_row = 0;
    }
else {
    *start_row = (int)proj->py;
    *end_row = PLAYFIELD_H -1;
}
if (*start_row > *end_row) {
    int temp = *start_row;
    *start_row = *end_row;
    *end_row = temp;
}
}
//Function that renders projectiles each frame
void render_projectiles(Projectile *projectiles, int max_x, int max_y){
for(int i=0; i < MAX_PROJECTILES; i++){
    if (projectiles[i].state == NORMAL && projectiles[i].type != LASER){
    attron(COLOR_PAIR(projectiles[i].color));
     mvaddch(offset_y + projectiles[i].py, offset_x + projectiles[i].px, projectiles[i].symbol);
     attroff(COLOR_PAIR(projectiles[i].color));
     refresh();
    }
    if (projectiles[i].state == NORMAL && projectiles[i].type == LASER){
get_laser_bounds(&projectiles[i], max_y, max_x, &start_row, &end_row);
for (int p = start_row; p <= end_row; p++) {
      attron(COLOR_PAIR(projectiles[i].color));
    mvaddch(offset_y + p, offset_x + projectiles[i].px, projectiles[i].symbol);
     attroff(COLOR_PAIR(projectiles[i].color));
}
    }
    
}
}
//Function that erases old positions of projectiles each frame and removes spent projectiles
void erase_projectiles(Projectile *projectiles, int max_x, int max_y){
    getmaxyx (stdscr, max_y, max_x);
    for(int i=0; i < MAX_PROJECTILES; i++){
        if (projectiles[i].state == NORMAL || projectiles[i].state == SPENT){  
    mvaddch(offset_y + projectiles[i].py, offset_x + projectiles[i].px, ' ');
     }
      if ( (projectiles[i].state == SPENT || projectiles[i].state == NORMAL) && projectiles[i].type == LASER){
get_laser_bounds(&projectiles[i], max_y, max_x, &start_row, &end_row);
for (int p = start_row; p <= end_row; p++) {
    mvaddch(offset_y + p, offset_x + projectiles[i].px, ' ');
}
    }
        }
    }
