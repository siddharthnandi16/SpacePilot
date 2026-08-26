#include <pdcurses.h>
#include  "gamedata.h"
#include "spawn.h"
//Game runs at 30 ticks per second and scrolls at 5 rows per second
//After editing spawn table, ALWAYS set spawn_count in level.c to the number of enemies in that table
spawn_entry spawn_table_1[]={
    [0] ={
.trigger = ROW, .type = HUNTER, .behavior = HUNT_PLAYER, .fired = FALSE, .px = 10, .py = 10, 
.strafe = 0, .trigger_time=10
    },
    [1] ={
.trigger = ROW, .type = FLYING_FORTRESS, .behavior = HUNT_PLAYER, .fired = FALSE,
 .px = 50, .py = 8, .strafe = 10, .trigger_time=0
    },
    [2] ={
.trigger = ROW, .type = LASER_JET, .behavior = STRAFE_HORIZONTAL, .fired = FALSE,
 .px = 60, .py = 5, .strafe = 40, .trigger_time=0
    },
    [3] ={
.trigger = ROW, .type = JET, .behavior = STRAFE_HORIZONTAL, 
.fired = FALSE, .px = 10, .py = 10, .strafe = 40, .trigger_time=0
    },
    [4] ={
.trigger = TICK, .type = JET, .behavior = HUNT_PLAYER, 
.fired = FALSE, .px = 1, .py = 1, .strafe = 30, .trigger_time=90
    }
};
