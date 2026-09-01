#include <pdcurses.h>
#include  "gamedata.h"
#include "spawn.h"
//Game runs at 30 ticks per second and scrolls at 5 rows per second
//After editing spawn table, ALWAYS set spawn_count in level.c to the number of enemies in that table
spawn_entry spawn_table_1[]={
    [0] ={
.trigger = ROW, .type = CARRIER_BOSS, .behavior = CARRIER_SPECIAL, .fired = FALSE, .px = 50, .py = 6, 
.strafe = 0, .trigger_time=0, .aimed = TRUE
    },

};
const int spawn_table_1_count = sizeof(spawn_table_1) / sizeof(spawn_table_1[0]);
spawn_entry spawn_table_2[]={
    [0] ={
.trigger = ROW, .type = FLYING_FORTRESS, .behavior = STATIC, .fired = FALSE, .px = 50, .py = 5, 
.strafe = 0, .trigger_time=0, .aimed = TRUE
    },
    [1] ={
.trigger = ROW, .type = HUNTER, .behavior = STATIC, .fired = FALSE, .px = 50, .py = 6, 
.strafe = 0, .trigger_time=60, .aimed = TRUE
    }
};
const int spawn_table_2_count = sizeof(spawn_table_2) / sizeof(spawn_table_2[0]);