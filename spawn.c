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
.trigger = ROW, .type = JET, .behavior = STATIC, .fired = FALSE,
 .px = 50, .py = 8, .strafe = 0, .trigger_time=0
    },
    [2] ={
.trigger = ROW, .type = LASER_ENEMY, .behavior = STATIC, .fired = FALSE,
 .px = 12, .py = 10, .strafe = 0, .trigger_time=40
    },
    [3] ={
.trigger = ROW, .type = JET, .behavior = STRAFE_HORIZONTAL, 
.fired = FALSE, .px = 10, .py = 10, .strafe = 10, .trigger_time=0
    },
    [4] ={
.trigger = TICK, .type = JET, .behavior = STRAFE_VERTICAL, 
.fired = FALSE, .px = 0, .py = 26, .strafe = 30, .trigger_time=90
    }
};
