#include <pdcurses.h>
#include <stdlib.h>
#include <math.h>
#include "gamedata.h"
#include "projectile.h"
#include "window.h"
#include "enemy.h"
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
    .weapon = &GRUNT_RIFLE,
    .fire_px=0,
    .fire_py=0,
    .aimed = FALSE
    
    }
};
//Backup of spawning pool
Enemy enemies_backup[MAX_ENEMIES] = {
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
    .weapon = &GRUNT_RIFLE,
    
    }
};
//Slowly fires bullets. Low-threat enemy, mostly just scoring fodder
static const Enemy grunt_template = {
    .px = 0, .py = 0,
    .dx = 1, .dy = 1,
    .hp = 1,
    .symbol = '%',
    .width = 1, .height = 1,
    .cooldown_frames = -30,
    .type = GRUNT,
    .state = INACTIVE,
    .behavior = STATIC,
    .shape = NULL,
    .weapon = &GRUNT_RIFLE,
    
};
// Rapidly fires bullets and moves fast. Meant to be dangerous in swarms
static const Enemy rapidfire_template = {
    .px = 0, .py = 0,
    .dx = 3, .dy = 3,
    .hp = 2,
    .symbol = '&',
    .width = 1, .height = 1,
    .cooldown_frames = -30,
    .type = RAPIDFIRE,
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
    .cooldown_frames = -30,
    .type = LASER_ENEMY,
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
    .cooldown_frames = -30,
    .type = BOMBER,
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
    .cooldown_frames = -30,
    .type = HUNTER,
    .state = INACTIVE,
    .behavior = STATIC,
    .shape = NULL,
    .weapon = &HUNTER_RIFLE
};
//Layout for jets
static const int jet_row0_colors[] = {2, 6, 2}; //red, amber, red
static const int jet_row1_colors[] = {2, 7, 2}; //red, steel gray, red
static const int jet_row2_colors[] = {2, 2, 2}; //red, red, red
// Anchor point is the # at its center
TileLayout Jet_Layout = {
.width = 3, .height = 3,
.glyph_rows = {
    " | ",
    "<#>",
    " V "
},
.color_rows = {
    jet_row0_colors,
    jet_row1_colors,
    jet_row2_colors
}
};
static const Enemy jet_template = {
    .px = 0, .py = 0,
    .dx = 2, .dy = 2,
    .hp = 10,
    .symbol = '%',
    .width = 3, .height = 3,
    .cooldown_frames = -30,
    .type = JET,
    .state = INACTIVE,
    .behavior = STATIC,
    .shape = &Jet_Layout,
    .weapon = &JET_CANNON
};
//Layout for flying fortresses
static const int flyfort_row0_colors[] = {2, 6, 6, 6, 2}; //red, amber, amber,amber, red
static const int flyfort_row1_colors[] = {2, 7, 7, 7, 2}; //red, steel gray, steel gray, steel gray, red
static const int flyfort_row2_colors[] = {2, 2, 7, 2, 2}; //red, red,steel gray, red, red
// Anchor point is the # at its center
TileLayout Flying_Fortress_Layout = {
.width = 5, .height = 3,
.glyph_rows = {
    " ||| ",
    "<###>",
    " \\#/ "
},
.color_rows = {
    flyfort_row0_colors,
    flyfort_row1_colors,
    flyfort_row2_colors
}
};
static const Enemy Flying_Fortress_template = {
    .px = 0, .py = 0,
    .dx = 1, .dy = 1,
    .hp = 20,
    .symbol = '%',
    .width = 5, .height = 3,
    .cooldown_frames = -60,
    .type = FLYING_FORTRESS,
    .state = INACTIVE,
    .behavior = STATIC,
    .shape = &Flying_Fortress_Layout,
    .weapon = &FLYFORT_CANNON
};
static const int laser_jet_row0_colors[] = {2, 6, 6, 2}; //red, amber, red
static const int laser_jet_row1_colors[] = {2, 7, 7, 2}; //red, steel gray, red
static const int laser_jet_row2_colors[] = {2, 3, 3, 2}; //red, yellow,yellow, red
TileLayout Laser_Jet_Layout = {
.width = 4, .height = 3,
.glyph_rows = {
    " || ",
    "<##>",
    " !! "
},
.color_rows = {
    laser_jet_row0_colors,
    laser_jet_row1_colors,
    laser_jet_row2_colors
}
};
static const Enemy laser_jet_template = {
    .px = 0, .py = 0,
    .dx = 3, .dy = 1,
    .hp = 8,
    .symbol = '%',
    .width = 4, .height = 3,
    .cooldown_frames = -120,
    .type = LASER_JET,
    .state = INACTIVE,
    .behavior = STATIC,
    .shape = &Laser_Jet_Layout,
    .weapon = &laserrifle
};
//Template for core of first boss
// Carrier boss shape — turret sockets marked '.', aircraft bays marked 'o'
// Use these positions (row, col) as reference offsets when placing turret/grunt-spawn subsystems relative to the core anchor
static  int carrier_colors_row0[10] = {7,7,6,7,7,6,7,7,6,7};
static  int carrier_colors_row1[10] = {2,2,2,2,2,2,2,2,2,2};
static  int carrier_colors_row2[10] = {7,7,7,7,7,7,7,7,7,7};
static  int carrier_colors_row3[10] = {7,7,2,7,7,7,7,2,7,7};
static  int carrier_colors_row4[10] = {7,2,2,7,7,7,7,2,2,7};
static int carrier_colors_row5[10] = {2,2,2,2,2,2,2,2,2,2};
static TileLayout carrier_layout = {
    .width = 10, .height = 6,
    .glyph_rows = {
        "  |  |  | ",
        "==========",
        "|########|",
        "|#.####.#|",
        "|..####..|",
        "=========="
    },
    .color_rows = {
        carrier_colors_row0, carrier_colors_row1, carrier_colors_row2,
        carrier_colors_row3, carrier_colors_row4, carrier_colors_row5
    }
};
static Enemy carrier_boss_core_template = {
    .px = 0, .py = 0,
    .dx = 0, .dy = 0,
    .hp = 80,
    .symbol = '%',
    .width = 10, .height = 6,
    .cooldown_frames = -120,
    .type = CARRIER_BOSS,
    .state = INACTIVE,
    .behavior = CARRIER_SPECIAL,
    .shape = &carrier_layout,
    .weapon = &HUNTER_RIFLE,
    .is_boss_part = 1, //Is part of the carrier boss
    .is_boss_core = 1 //Is core of the carrier boss
};
//Special layout to be used during the invuln state
static const int carrier_invuln_colors_row0[10] = {7,7,6,7,7,6,7,7,6,7}; // contrails unchanged
static const int carrier_invuln_colors_row1[10] = {9,9,9,9,9,9,9,9,9,9}; // top edge -> purple
static const int carrier_invuln_colors_row2[10] = {7,7,7,7,7,7,7,7,7,7}; // hull unchanged
static const int carrier_invuln_colors_row3[10] = {7,7,9,7,7,7,7,9,7,7}; // turret sockets -> purple
static const int carrier_invuln_colors_row4[10] = {7,9,9,7,7,7,7,9,9,7}; // aircraft bays -> purple
static const int carrier_invuln_colors_row5[10] = {9,9,9,9,9,9,9,9,9,9}; // bottom edge -> purple

static TileLayout carrier_layout_invuln = {
    .width = 10, .height = 6,
    .glyph_rows = {
        "  |  |  | ",
        "==========",
        "|########|",
        "|#.####.#|",
        "|..####..|",
        "=========="
    },
    .color_rows = {
        carrier_invuln_colors_row0, carrier_invuln_colors_row1, carrier_invuln_colors_row2,
        carrier_invuln_colors_row3, carrier_invuln_colors_row4, carrier_invuln_colors_row5
    }
};
//Layout for carrier's machine guns
static const int mg_colors_row0[2] = {3, 3};
static const int mg_colors_row1[2] = {2, 2};
static const int mg_colors_row2[2] = {2, 2};
static const int mg_colors_row3[2] = {3, 3};

static TileLayout flakgun_layout = {
    .width = 2, .height = 4,
    .glyph_rows = {
        "^^",
        "##",
        "##",
        "vv"
    },
    .color_rows = {
        mg_colors_row0, mg_colors_row1, mg_colors_row2, mg_colors_row3
    }
};
static Enemy carrier_boss_FLAK_template = {
    .px = 0, .py = 0,
    .dx = 0, .dy = 0,
    .hp = 15,
    .symbol = '%',
    .width = 2, .height = 4,
    .cooldown_frames = -60,
    .type = CARRIER_BOSS_FLAK,
    .state = INACTIVE,
    .behavior = STATIC,
    .shape = &flakgun_layout,
    .weapon = &CARRIER_FLAK,
    .is_boss_part = 1, //Is part of the carrier boss
    .is_boss_core = 0 
};
//Bomb launcher of carrier boss
static const int bc_colors_row0[3] = {3, 3, 3};
static const int bc_colors_row1[3] = {2, 2, 2};
static const int bc_colors_row2[3] = {2, 2, 2};
static const int bc_colors_row3[3] = {2, 2, 2};
static const int bc_colors_row4[3] = {3, 3, 3};

static TileLayout bombcannon_layout = {
    .width = 3, .height = 5,
    .glyph_rows = {
        "/#\\",
        "###",
        "###",
        "###",
        "\\#/"
    },
    .color_rows = {
        bc_colors_row0, bc_colors_row1, bc_colors_row2, bc_colors_row3, bc_colors_row4
    }
};
static Enemy carrier_boss_bomb_template = {
    .px = 0, .py = 0,
    .dx = 0, .dy = 0,
    .hp = 15,
    .symbol = '%',
    .width = 3, .height = 5,
    .cooldown_frames = -60,
    .type = CARRIER_BOSS_BOMB,
    .state = INACTIVE,
    .behavior = STATIC,
    .shape = &bombcannon_layout,
    .weapon = &CARRIER_CANNON,
    .is_boss_part = 1, //Is part of the carrier boss
    .is_boss_core = 0 
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
        case JET:       return &jet_template;
        case FLYING_FORTRESS: return &Flying_Fortress_template;
        case LASER_JET: return &laser_jet_template;
        case CARRIER_BOSS: return &carrier_boss_core_template;
        case CARRIER_BOSS_FLAK: return &carrier_boss_FLAK_template;
        case CARRIER_BOSS_BOMB: return &carrier_boss_bomb_template;
        default:        return NULL;
    }
}
//Spawns enemies. Can take arguments to set their type, behavior, spawn point, anchor point, and strafe values
void spawn_enemy(EnemyType type, EnemyBehavior behavior, bool aimed, float px, float py, float strafe){
int slot = findfreeslot();
if (slot == -1){
    return;
}
const Enemy *template = get_template(type);
if (template == NULL) {
    return; //Unknown type, exits the function
}

enemies[slot] = *template;
if(aimed == TRUE){
    enemies[slot].aimed = TRUE;
}
enemies[slot].px = px;
enemies[slot].py = py;
enemies[slot].old_px = px;
enemies[slot].old_py = py;
enemies[slot].strafe = strafe;
enemies[slot].anchor_px = enemies[slot].px;
enemies[slot].anchor_py = enemies[slot].py;
enemies[slot].fire_px = enemies[slot].px;
enemies[slot].fire_py = enemies[slot].py;
enemies[slot].behavior = behavior;
enemies[slot].state = ALIVE;
if (enemies[slot].shape != NULL){
enemies[slot].px = enemies[slot].px - (template->shape->width  / 2.0f);
enemies[slot].py = enemies[slot].py - (template->shape->height / 2.0f);
enemies[slot].fire_px = enemies[slot].px + ceilf(enemies[slot].width / 2.0f);
enemies[slot].fire_py = enemies[slot].py + ceilf(enemies[slot].height / 2.0f);
enemies[slot].anchor_px = enemies[slot].px;
enemies[slot].anchor_py = enemies[slot].py;
} 
}
//Function that moves living enemies based on their behavior type and removes dead enemies
void move_enemy(Enemy *enemies, Player *player, int max_x, int max_y){
for (int i =0; i < MAX_ENEMIES; i++ ){
    enemies[i].age++;
    if (enemies[i].state == ALIVE){
if(enemies[i].shape !=NULL){
enemies[i].fire_px = enemies[i].px + ceilf(enemies[i].width / 2.0f);
enemies[i].fire_py = enemies[i].py + ceilf(enemies[i].height / 2.0f);}
else {
enemies[i].fire_px = enemies[i].px ;
enemies[i].fire_py = enemies[i].py;
}
switch(enemies[i].behavior){
    case STATIC:
    break; //No need to move them since they are stationary by design
    case MOVEVERTICALLY: //Moves vertically downwards and then despawns
    enemies[i].py = enemies[i].py + enemies[i].dy;
    if (enemies[i].py >= PLAYFIELD_H - 1) {
enemies[i].state = DEAD; //Despawns upon hitting the bottom edge of the screen
    }
break;
case MOVEHORIZONTALLY: //Moves from left to right and then despawms
enemies[i].px = enemies[i].px + enemies[i].dx;
 if (enemies[i].px >= PLAYFIELD_W - 1) {
enemies[i].state = DEAD; //Despawns upon hitting the right edge of the screen
 }
break;
case STRAFE_HORIZONTAL:
enemies[i].px = enemies[i].px + enemies[i].dx;
//Reverses direction if it goes too far from its anchor point or hits a border
if (fabs(enemies[i].anchor_px - enemies[i].px) > enemies[i].strafe){
  enemies[i].dx = -enemies[i].dx; 
  enemies[i].px = enemies[i].px + enemies[i].dx;
}
if ((int)enemies[i].px + enemies[i].width - 1 >= PLAYFIELD_W){
   enemies[i].dx = -enemies[i].dx;
   enemies[i].px = PLAYFIELD_W - enemies[i].width;
}
if  (enemies[i].px + enemies[i].width -1 <= 0 ){
enemies[i].dx = -enemies[i].dx;
enemies[i].px =  enemies[i].width;
}
break;
case STRAFE_VERTICAL:
enemies[i].py = enemies[i].py + enemies[i].dy;
//Reverses direction if it goes too far from its anchor point or hits a border
if (fabs(enemies[i].anchor_py - enemies[i].py) > enemies[i].strafe) 
enemies[i].dy = -enemies[i].dy;
enemies[i].py = enemies[i].py + enemies[i].dy;
//Boundary checking code
if ((int)enemies[i].py + enemies[i].height -1 >= PLAYFIELD_H-1){
    enemies[i].dy = -enemies[i].dy;
    enemies[i].py = PLAYFIELD_H - enemies[i].height;
}
if  (enemies[i].py + enemies[i].height -1 <= 0){
enemies[i].dy = -enemies[i].dy;
enemies[i].py = enemies[i].height;
}
break;
// Hunters will attempt to get within 4 rows of the player 
// and then attack with their rapid-firing cannons.
// They will always attempt to be on the same column as the player
// They will never go below the player
case HUNT_PLAYER:
static int hunt_tick = 0;
hunt_tick++;
if (hunt_tick % 4 == 0){
if (enemies[i].px < player->px) enemies[i].px +=  enemies[i].dx;
if (enemies[i].px > player->px) enemies[i].px -=  enemies[i].dx;
float target_py = player->py - 4;
if (enemies[i].py < target_py ) enemies[i].py += enemies[i].dy;
if (enemies[i].py > target_py ) enemies[i].py -= enemies[i].dy;
}
if ((int)enemies[i].px + enemies[i].width - 1 >= PLAYFIELD_W){
   enemies[i].dx = -enemies[i].dx;
   enemies[i].px = PLAYFIELD_W -1;
}
if  (enemies[i].px + enemies[i].width -1 == 0 ){
enemies[i].dx = -enemies[i].dx;
enemies[i].px -=  enemies[i].dx;
}
if ((int)enemies[i].py + enemies[i].height -1 >= PLAYFIELD_H-1){
    enemies[i].dy = -enemies[i].dy;
    enemies[i].py - PLAYFIELD_H - 1;
}
if  (enemies[i].py + enemies[i].height -1 <= 0){
enemies[i].dy = -enemies[i].dy;
enemies[i].py = 1;
}
break;
case HUNT_PLAYER_FAR:
static int hunt_tick_2 = 0;
hunt_tick_2++;
if (hunt_tick_2 % 4 == 0){
if (enemies[i].px < player->px) enemies[i].px +=  enemies[i].dx;
if (enemies[i].px > player->px) enemies[i].px -=  enemies[i].dx;
float target_py = player->py - 8;
if (enemies[i].py < target_py ) enemies[i].py += enemies[i].dy;
if (enemies[i].py > target_py ) enemies[i].py -= enemies[i].dy;
}
if ((int)enemies[i].px + enemies[i].width - 1 >= PLAYFIELD_W){
   enemies[i].dx = -enemies[i].dx;
   enemies[i].px = PLAYFIELD_W -1;
}
if  (enemies[i].px + enemies[i].width -1 == 0 ){
enemies[i].dx = -enemies[i].dx;
enemies[i].px -=  enemies[i].dx;
}
if ((int)enemies[i].py + enemies[i].height -1 >= PLAYFIELD_H-1){
    enemies[i].dy = -enemies[i].dy;
    enemies[i].py - PLAYFIELD_H - 1;
}
if  (enemies[i].py + enemies[i].height -1 <= 0){
enemies[i].dy = -enemies[i].dy;
enemies[i].py = 1;
}
break;
case CARRIER_SPECIAL:
if (BOSS_NORMAL == TRUE){
break;}
boss_state_timer++;
if (boss_state_timer % 500 == 0){
spawn_enemy(GRUNT, HUNT_PLAYER, false, enemies[i].px + (enemies[i].width/3),
 enemies[i].py + enemies[i].height + 2, 0);
 spawn_enemy(GRUNT, HUNT_PLAYER, false, enemies[i].px + (enemies[i].width/3 + 1),
 enemies[i].py + enemies[i].height + 2, 0);
 spawn_enemy(GRUNT, HUNT_PLAYER, false, enemies[i].px + (enemies[i].width/3 + 2),
 enemies[i].py + enemies[i].height + 2, 0);
 spawn_enemy(HUNTER, HUNT_PLAYER, false, enemies[i].px + (enemies[i].width/3 + 2),
 enemies[i].py + enemies[i].height + 2, 0);
} 
if (enemies[i].hp < 50 && state == BOSS_NORMAL) {
    state = SPECIAL_ATTACK_1;
    static int carrier_colors_row5[10] = {2,2,2,2,2,2,2,2,2,2};
spawn_enemy(CARRIER_BOSS_FLAK, STATIC, false, enemies[i].px + (enemies[i].width/3),
 enemies[i].py + enemies[i].height + 2, 0);
}
if (enemies[i].hp < 20 && state == SPECIAL_ATTACK_1){
for(int core = 0; core <= MAX_ENEMIES; core++){
    if(enemies[core].is_boss_core == TRUE){
    enemies[core].shape = &carrier_layout_invuln;
    }
}
    state = SPECIAL_ATTACK_2;
    boss_state_timer = 0;
    boss_invulnerable = TRUE; 
spawn_enemy(CARRIER_BOSS_BOMB, STATIC, false, enemies[i].px + (2*enemies[i].width/3 + 3),
 enemies[i].py + enemies[i].height + 3, 0);
}
if (boss_state_timer >= 240 && state == SPECIAL_ATTACK_2){
boss_invulnerable = FALSE;
for(int core = 0; core <= MAX_ENEMIES; core++){
    if(enemies[core].is_boss_core == TRUE){
    enemies[core].shape = &carrier_layout;
    }
}
}
default:
break;
} 
}
}
}
//Function that erases the old positions of enemies each frame
void erase_enemies(Enemy *enemies){
    for(int i=0; i < MAX_ENEMIES; i++){
        if (enemies[i].shape == NULL && (enemies[i].state == ALIVE || enemies[i].state == DEAD)){
if (enemies[i].shape == NULL){   
    mvaddch(offset_y + enemies[i].py, offset_x + enemies[i].px, ' ');
     enemies[i].old_px = enemies[i].px;
    enemies[i].old_py = enemies[i].py;
    if (enemies[i].state == DEAD) {
        enemies[i].state = INACTIVE;
    }
     }
             }
             if (enemies[i].shape != NULL && (enemies[i].state ==ALIVE || enemies[i].state == DEAD)){
const TileLayout *shape = enemies[i].shape;
    for (int row = 0; row < shape->height; row++) {
        for (int col = 0; col < shape->width; col++) {
            char glyph = shape->glyph_rows[row][col];
            // Does not render anything in blank cells
            if (glyph == ' ') continue;
            int color = shape->color_rows[row][col];
            attron(COLOR_PAIR(color));
            mvaddch(offset_y + (int)enemies[i].py + row,
            offset_x + (int)enemies[i].px + col,
            ' ');
            attroff(COLOR_PAIR(color));
        }
    }
     }

    }
}
//Function that renders living enemies
void render_enemies(Enemy *enemies){
for(int i=0; i < MAX_ENEMIES; i++){
   /* if (enemies[i].state != INACTIVE){
    fprintf(stderr, "%d %d %d",i, enemies[i].state, enemies[i].shape);
    } */
    if (enemies[i].shape == NULL && enemies[i].state == ALIVE){
    attron(COLOR_PAIR(2));
     mvaddch(offset_y + enemies[i].py, offset_x + enemies[i].px, enemies[i].symbol);
     attroff(COLOR_PAIR(2));
     wnoutrefresh(stdscr);
     //This block renders all multi-tile enemies
    }
    
     if (enemies[i].shape != NULL && enemies[i].state ==ALIVE){
      //  fprintf(stderr, "rendering shape enemy at %d\n", i);
const TileLayout *shape = enemies[i].shape;
    for (int row = 0; row < shape->height; row++) {
        for (int col = 0; col < shape->width; col++) {
            char glyph = shape->glyph_rows[row][col];
            // Does not render anything in blank cells
            if (glyph == ' ') continue;
            int color = shape->color_rows[row][col];
            attron(COLOR_PAIR(color));
            mvaddch(offset_y + (int)enemies[i].py + row,
            offset_x + (int)enemies[i].px + col,
            glyph);
            attroff(COLOR_PAIR(color));
            wnoutrefresh(stdscr);
        }
    }
     }
}
}
//Function that fires enemy weapons
void fire_enemies(Enemy *enemies, Player *player){
    
    for (int i =0 ; i < MAX_ENEMIES ; i++){
    float fire_angle = 270; // default downward angle, same as current behavior

if (enemies[i].aimed == TRUE) {
    float dx = player->px - enemies[i].px;
    float dy = player->py - (enemies[i].py - 1); // matches the py-1 fire origin you already use

    float ideal_rad = atan2f(-dy, dx); // negative dy since up = decreasing py, matches your missile code
    float ideal_deg = ideal_rad * (180.0f / M_PI);

    int inaccuracy = 15; // degrees of max random offset, tune to taste
    float offset = (rand() % (inaccuracy * 2 + 1)) - inaccuracy;

    fire_angle = ideal_deg + offset;
}
        if (enemies[i].state == ALIVE){
            enemies[i].cooldown_frames++;
        WeaponType *weapon = enemies[i].weapon;
         if (weapon != NULL && enemies[i].cooldown_frames >= weapon->cooldown_frames) {
            fire_weapon(weapon, enemies[i].fire_px, enemies[i].fire_py + 1, fire_angle, FALSE);
            enemies[i].cooldown_frames = 0;
            if (weapon->type == LASER) enemies[i].cooldown_frames = -300;
        }
    }
}
}
