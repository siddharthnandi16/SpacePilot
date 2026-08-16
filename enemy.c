#include <pdcurses.h>
#include <stdlib.h>
#include "gamedata.h"
#define MAX_ENEMIES 100
//Spawning pool for enemies. Values here are placeholders that will be overwritten during spawning
Enemy enemies[MAX_ENEMIES] = {
    [0] = {
.px = 0, .py = 0,
    .dx = 1, .dy = 1,
    .hp = 1,
    .symbol = '%',
    .width = 1, .height = 1,
    .cooldown_frames = 120,
    .type = GRUNT,
    .state = INACTIVE,
    .behavior = STATIC,
    .shape = NULL   
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
    .shape = NULL
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
    .shape = NULL
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
    .shape = NULL
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
    .shape = NULL
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
    .shape = NULL
};
//Function to find a free slot in the enemy pool
int findfreeslot(void){
    for(int i=0; i < MAX_ENEMIES; i++){
        if (enemies[i].state = INACTIVE){
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
        case LASER:     return &laser_template;
        case BOMBER:    return &bomber_template;
        case HUNTER:    return &hunter_template;
  //      case JET:       return &jet_template;
  // Commented out since it is not yet implemented
        default:        return NULL;
    }
}
//Spawns enemies. Can take arguments to set their type, behavior and spawn point
void spawn_enemy(EnemyType type, EnemyBehavior behavior, float px, float py){
int slot = findfreeslot();
if (slot == -1){
    return;
}
const Enemy *template = get_template(type);
if (template == NULL) {
    return; //Unknown type, breaks the function
}
enemies[slot] = *template;
enemies[slot].px = px;
enemies[slot].py = py;
enemies[slot].behavior = behavior;
enemies[slot].state = ALIVE;
}


