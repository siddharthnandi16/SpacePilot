#include <pdcurses.h>
#include <stdlib.h>
#include <math.h>
#include "gamedata.h"
#include "projectile.h"
#define MAX_ENEMIES 100
//Spawning pool for enemies. Values here are placeholders that will be overwritten during spawning
Enemy enemies[MAX_ENEMIES] = {
    [0] = {
.px = 0, .py = 0,
    .dx = 1, .dy = 1,
    .hp = 1,
    .symbol = '%',
    .width = 1, .height = 1,
    .cooldown_frames = 0, //Stores the firing timer
    .type = GRUNT,
    .state = INACTIVE,
    .behavior = STATIC,
    .shape = NULL,
    .weapon = &GRUNT_RIFLE
    }
};
//Slowly fires bullets. Low-threat enemy, mostly just scoring fodder
static const Enemy grunt_template = {
    .px = 0, .py = 0,
    .dx = 1, .dy = 1,
    .hp = 1,
    .symbol = '%',
    .width = 1, .height = 1,
    .cooldown_frames = 120,
    .type = GRUNT,
    .state = INACTIVE,
    .behavior = STATIC,
    .shape = NULL,
    .weapon = &GRUNT_RIFLE
};
// Rapidly fires bullets. Meant to be dangerous in swarms
static const Enemy rapidfire_template = {
    .px = 0, .py = 0,
    .dx = 2, .dy = 2,
    .hp = 1,
    .symbol = '&',
    .width = 1, .height = 1,
    .cooldown_frames = 10,
    .type = GRUNT,
    .state = INACTIVE,
    .behavior = STATIC,
    .shape = NULL,
    .weapon = &RAPIDFIRE_RIFLE
};
//Shoots lasers that travel in a straight line. A dangerous, high-priority target
static const Enemy laser_template = {
    .px = 0, .py = 0,
    .dx = 1, .dy = 1,
    .hp = 2,
    .symbol = '!',
    .width = 1, .height = 1,
    .cooldown_frames = 120,
    .type = GRUNT,
    .state = INACTIVE,
    .behavior = STATIC,
    .shape = NULL,
    .weapon = &LASER_RIFLE_ENEMY
};
//Fire bombs that explode into circles of bullets.A dangerous, high-priority target
static const Enemy bomber_template = {
    .px = 0, .py = 0,
    .dx = 1, .dy = 1,
    .hp = 2,
    .symbol = '#',
    .width = 1, .height = 1,
    .cooldown_frames = 180,
    .type = GRUNT,
    .state = INACTIVE,
    .behavior = STATIC,
    .shape = NULL,
    .weapon = &BOMB_ENEMY_WEAPON
};
//Hunts the player while rapidly firing bullets. The most dangerous basic enemy
static const Enemy hunter_template = {
    .px = 0, .py = 0,
    .dx = 1, .dy = 1,
    .hp = 4,
    .symbol = 'H',
    .width = 1, .height = 1,
    .cooldown_frames = 30,
    .type = GRUNT,
    .state = INACTIVE,
    .behavior = STATIC,
    .shape = NULL,
    .weapon = &HUNTER_RIFLE
};
//Function to find a free slot in the enemy pool
int findfreeslot(void){
    for(int i=0; i < MAX_ENEMIES; i++){
        if (enemies[i].state == INACTIVE){
            return i;
        }
    }
return -1; //No valid slot found
}
//Finds the address of a template and returns it. Add a new case each time a new template is made
const Enemy* get_template(EnemyType type) {
    switch (type) {
        case GRUNT:     return &grunt_template;
        case RAPIDFIRE: return &rapidfire_template;
        case LASER_ENEMY:     return &laser_template;
        case BOMBER:    return &bomber_template;
        case HUNTER:    return &hunter_template;
  //      case JET:       return &jet_template;
  // Commented out since it is not yet implemented
        default:        return NULL;
    }
}
//Spawns enemies. Can take arguments to set their type, behavior, spawn point, anchor point, and strafe values
void spawn_enemy(EnemyType type, EnemyBehavior behavior, float px, float py, float strafe){
int slot = findfreeslot();
if (slot == -1){
    return;
}
const Enemy *template = get_template(type);
if (template == NULL) {
    return; //Unknown type, exits the function
}
enemies[slot] = *template;
enemies[slot].px = px;
enemies[slot].py = py;
enemies[slot].old_px = px;
enemies[slot].old_py = py;
enemies[slot].strafe = strafe;
enemies[slot].anchor_px = enemies[slot].px;
enemies[slot].anchor_py = enemies[slot].py;
enemies[slot].behavior = behavior;
enemies[slot].state = ALIVE;
}
//Function that moves living enemies based on their behavior type
void move_enemy(Enemy *enemies, int max_x, int max_y){
for (int i =0; i < MAX_ENEMIES; i++ ){
    enemies[i].age++;
    if (enemies[i].state == ALIVE){
switch(enemies[i].behavior){
    case STATIC:
    break; //No need to move them since they are stationary by design
    case MOVEVERTICALLY: //Moves vertically downwards and then despawns
    enemies[i].py = enemies[i].py + enemies[i].dy;
    if (enemies[i].py >= max_y - 1) {
enemies[i].state = DEAD; //Despawns upon hitting the bottom edge of the screen
    }
break;
case MOVEHORIZONTALLY: //Moves from left to right and then despawms
enemies[i].px = enemies[i].px + enemies[i].dx;
 if (enemies[i].py >= max_x - 1) {
enemies[i].state = DEAD; //Despawns upon hitting the right edge of the screen
 }
break;
case STRAFE_HORIZONTAL:
enemies[i].px = enemies[i].px + enemies[i].dx;
//Reverses direction if it goes too far from its anchor point or hits a border
if (fabs(enemies[i].anchor_px - enemies[i].px) > enemies[i].strafe || enemies[i].px == max_x-1 || enemies[i].px == 0){
enemies[i].dx = -enemies[i].dx;
}
break;
case STRAFE_VERTICAL:
enemies[i].py = enemies[i].py + enemies[i].dy;
//Reverses direction if it goes too far from its anchor point or hits a border
if (fabs(enemies[i].anchor_py - enemies[i].py) > enemies[i].strafe || enemies[i].px == max_x-1 || enemies[i].px == 0){
enemies[i].dy = -enemies[i].dy;
}
break;
default:
break;
    }
}
}
}
//Function that erases the old positions of enemies each frame
void erase_enemies(Enemy *enemies){
    for(int i=0; i < MAX_ENEMIES; i++){
        if (enemies[i].state == ALIVE){
if (enemies[i].shape == NULL){   
    mvaddch(enemies[i].py, enemies[i].px, ' ');
     enemies[i].old_px = enemies[i].px;
    enemies[i].old_py = enemies[i].py;
     }
        }
    }
}
void render_enemies(Enemy *enemies){
for(int i=0; i < MAX_ENEMIES; i++){
    if (enemies[i].state == ALIVE){
    attron(COLOR_PAIR(2));
     mvaddch(enemies[i].py, enemies[i].px, enemies[i].symbol);
     attroff(COLOR_PAIR(2));
     refresh();
    }
}
}
    
