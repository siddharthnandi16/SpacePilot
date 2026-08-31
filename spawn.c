#include <pdcurses.h>
#include  "gamedata.h"
#include "spawn.h"
//Game runs at 30 ticks per second and scrolls at 5 rows per second
//After editing spawn table, ALWAYS set spawn_count in level.c to the number of enemies in that table
spawn_entry spawn_table_1[]={
    [0] ={
.trigger = ROW, .type = CARRIER_BOSS, .behavior = CARRIER_SPECIAL, .fired = FALSE, .px = 50, .py = 6, 
.strafe = 0, .trigger_time=1500, .aimed = TRUE
    },
    [1] ={
.trigger = ROW, .type = GRUNT, .behavior = STATIC, .fired = FALSE, .px = 50, .py = 6, 
.strafe = 0, .trigger_time=0, .aimed = TRUE
    },
    [2] ={
.trigger = ROW, .type = GRUNT, .behavior = STATIC, .fired = FALSE, .px = 45, .py = 6, 
.strafe = 0, .trigger_time=0, .aimed = TRUE
    },
    [3] ={
.trigger = ROW, .type = GRUNT, .behavior = STATIC, .fired = FALSE, .px = 55, .py = 6, 
.strafe = 0, .trigger_time=0, .aimed = TRUE
    },
    [4] ={
.trigger = ROW, .type = GRUNT, .behavior = STATIC, .fired = FALSE, .px = 55, .py = 6, 
.strafe = 0, .trigger_time=0, .aimed = TRUE
    },
    [5] ={
.trigger = ROW, .type = RAPIDFIRE, .behavior = STATIC, .fired = FALSE, .px = 50, .py = 6, 
.strafe = 10, .trigger_time=60, .aimed = TRUE
    },
    [6] ={
.trigger = ROW, .type = RAPIDFIRE, .behavior = STATIC, .fired = FALSE, .px = 60, .py = 6, 
.strafe = 10, .trigger_time=60, .aimed = TRUE
    },
    [7] ={
.trigger = ROW, .type = RAPIDFIRE, .behavior = STATIC, .fired = FALSE, .px = 40, .py = 6, 
.strafe = 10, .trigger_time=60, .aimed = TRUE
    },
    [8] ={
.trigger = ROW, .type = BOMBER, .behavior = STATIC, .fired = FALSE, .px = 10, .py = 6, 
.strafe = 10, .trigger_time=150, .aimed = FALSE
    },
    [9] ={
.trigger = ROW, .type = BOMBER, .behavior = STATIC, .fired = FALSE, .px = 80, .py = 6, 
.strafe = 10, .trigger_time=150, .aimed = FALSE
    },
    [10] ={
.trigger = ROW, .type = LASER_ENEMY, .behavior = STRAFE_HORIZONTAL, .fired = FALSE, .px = 20, .py = 2, 
.strafe = 10, .trigger_time=240, .aimed = FALSE
    },
    [11] ={
.trigger = ROW, .type = LASER_ENEMY, .behavior = STATIC, .fired = FALSE, .px = 50, .py = 2, 
.strafe = 10, .trigger_time=240, .aimed = FALSE
    },
    [12] ={
.trigger = ROW, .type =BOMBER , .behavior = STRAFE_VERTICAL, .fired = FALSE, .px = 85, .py = 2, 
.strafe = 10, .trigger_time=360, .aimed = FALSE
    },
    [13] ={
.trigger = ROW, .type =RAPIDFIRE , .behavior = HUNT_PLAYER_FAR, .fired = FALSE, .px = 15, .py = 1, 
.strafe = 10, .trigger_time=420, .aimed = FALSE
    },
    [14] ={
.trigger = ROW, .type =GRUNT , .behavior = HUNT_PLAYER_FAR, .fired = FALSE, .px = 15, .py = 1, 
.strafe = 10, .trigger_time=420, .aimed = FALSE
    },
    [15] ={
.trigger = ROW, .type =GRUNT , .behavior = HUNT_PLAYER_FAR, .fired = FALSE, .px = 15, .py = 1, 
.strafe = 10, .trigger_time=420, .aimed = FALSE
    },  
    [16] ={
.trigger = ROW, .type =GRUNT , .behavior = MOVEVERTICALLY, .fired = FALSE, .px = 15, .py = 1, 
.strafe = 10, .trigger_time=510, .aimed = FALSE
    },
    [17] ={
.trigger = ROW, .type =GRUNT , .behavior = MOVEVERTICALLY, .fired = FALSE, .px = 20, .py = 1, 
.strafe = 10, .trigger_time=510, .aimed = FALSE
    },
    [18] ={
.trigger = ROW, .type =GRUNT , .behavior = MOVEVERTICALLY, .fired = FALSE, .px = 25, .py = 1, 
.strafe = 10, .trigger_time=510, .aimed = FALSE
    },
    [19] ={
.trigger = ROW, .type =GRUNT , .behavior = MOVEVERTICALLY, .fired = FALSE, .px = 25, .py = 1, 
.strafe = 10, .trigger_time=510, .aimed = FALSE
    },
    [20] ={
.trigger = ROW, .type =GRUNT , .behavior = MOVEVERTICALLY, .fired = FALSE, .px = 30, .py = 1, 
.strafe = 10, .trigger_time=510, .aimed = FALSE
    },
    [21] ={
.trigger = ROW, .type =GRUNT , .behavior = MOVEVERTICALLY, .fired = FALSE, .px = 35, .py = 1, 
.strafe = 10, .trigger_time=510, .aimed = FALSE
    },
    [22] ={
.trigger = ROW, .type =GRUNT , .behavior = MOVEVERTICALLY, .fired = FALSE, .px = 40, .py = 1, 
.strafe = 10, .trigger_time=510, .aimed = FALSE
    },
    [23] ={
.trigger = ROW, .type =GRUNT , .behavior = MOVEVERTICALLY, .fired = FALSE, .px = 45, .py = 1, 
.strafe = 10, .trigger_time=510, .aimed = FALSE
    },
    [24] ={
.trigger = ROW, .type =GRUNT , .behavior = MOVEVERTICALLY, .fired = FALSE, .px = 50, .py = 1, 
.strafe = 10, .trigger_time=510, .aimed = FALSE
    },
    [25] ={
.trigger = ROW, .type =GRUNT , .behavior = MOVEVERTICALLY, .fired = FALSE, .px = 55, .py = 1, 
.strafe = 10, .trigger_time=510, .aimed = FALSE
    },
    [26] ={
.trigger = ROW, .type =GRUNT , .behavior = MOVEVERTICALLY, .fired = FALSE, .px = 60, .py = 1, 
.strafe = 10, .trigger_time=510, .aimed = FALSE
    },
};
const int spawn_table_1_count = sizeof(spawn_table_1) / sizeof(spawn_table_1[0]);
spawn_entry spawn_table_2[]={
    [0] ={
.trigger = ROW, .type = FLYING_FORTRESS, .behavior = STATIC, .fired = FALSE, .px = 50, .py = 2, 
.strafe = 0, .trigger_time=0, .aimed = TRUE
    },
    [1] ={
.trigger = ROW, .type = HUNTER, .behavior = STATIC, .fired = FALSE, .px = 50, .py = 6, 
.strafe = 0, .trigger_time=60, .aimed = TRUE
    }
};
const int spawn_table_2_count = sizeof(spawn_table_2) / sizeof(spawn_table_2[0]);