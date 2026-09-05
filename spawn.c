#include <pdcurses.h>
#include  "gamedata.h"
#include "spawn.h"
//Game runs at 30 ticks per second and scrolls at 5 rows per second
//After editing spawn table, ALWAYS set spawn_count in level.c to the number of enemies in that table
//Old version of level 1, commented out due to being unbalanced
/*spawn_entry spawn_table_1[]={
    //Total time until reaching boss of level 1 = 1200
    [0] ={
.trigger = ROW, .type = CARRIER_BOSS, .behavior = CARRIER_SPECIAL, .fired = FALSE, .px = 50, .py = 6, 
.strafe = 0, .trigger_time=1200, .aimed = TRUE
    },
    [1] ={
.trigger = ROW, .type = GRUNT, .behavior = STATIC, .fired = FALSE, .px = 50, .py = 4, 
.strafe = 0, .trigger_time=90, .aimed = FALSE
    },
    [2] ={
.trigger = ROW, .type = GRUNT, .behavior = STATIC, .fired = FALSE, .px = 70, .py = 4, 
.strafe = 0, .trigger_time=90, .aimed = FALSE
    },
    [3] ={
.trigger = ROW, .type = GRUNT, .behavior = STATIC, .fired = FALSE, .px = 80, .py = 4, 
.strafe = 0, .trigger_time=90, .aimed = FALSE
    },
    [4] ={
.trigger = ROW, .type = GRUNT, .behavior = STATIC, .fired = FALSE, .px = 40, .py = 4, 
.strafe = 0, .trigger_time=90, .aimed = FALSE
    },
    [5] ={
.trigger = ROW, .type = GRUNT, .behavior = STATIC, .fired = FALSE, .px = 30, .py = 4, 
.strafe = 0, .trigger_time=90, .aimed = FALSE
    },
    [6] ={
.trigger = ROW, .type = GRUNT, .behavior = STRAFE_HORIZONTAL, .fired = FALSE, .px = 30, .py = 3, 
.strafe = 10, .trigger_time=120, .aimed = FALSE
    },
    [7] ={
.trigger = ROW, .type = GRUNT, .behavior = STRAFE_HORIZONTAL, .fired = FALSE, .px = 50, .py = 3, 
.strafe = 10, .trigger_time=120, .aimed = FALSE
    },
    [8] ={
.trigger = ROW, .type = GRUNT, .behavior = HUNT_PLAYER_FAR, .fired = FALSE, .px = 10, .py = 1, 
.strafe = 10, .trigger_time=150, .aimed = FALSE
    },
    [9] ={
.trigger = ROW, .type = GRUNT, .behavior = HUNT_PLAYER_FAR, .fired = FALSE, .px = 90, .py = 3, 
.strafe = 10, .trigger_time=150, .aimed = FALSE
    },
    [10] ={
.trigger = ROW, .type = GRUNT, .behavior = STATIC, .fired = FALSE, .px = 5, .py = 5, 
.strafe = 10, .trigger_time=210, .aimed = TRUE
    },
    [11] ={
.trigger = ROW, .type = GRUNT, .behavior = STATIC, .fired = FALSE, .px = 95, .py = 5, 
.strafe = 10, .trigger_time=210, .aimed = TRUE
    },
    [12] ={
.trigger = ROW, .type = GRUNT, .behavior = STRAFE_HORIZONTAL, .fired = FALSE, .px = 75, .py = 3, 
.strafe = 25, .trigger_time=270, .aimed = TRUE
    },
    [13] ={
.trigger = ROW, .type = GRUNT, .behavior = STRAFE_HORIZONTAL, .fired = FALSE, .px = 25, .py = 3, 
.strafe = 25, .trigger_time=270, .aimed = TRUE
    },
    [14] ={
.trigger = ROW, .type = GRUNT, .behavior = STATIC, .fired = FALSE, .px = 95, .py = 10, 
.strafe = 10, .trigger_time=280, .aimed = FALSE
    },
    [15] ={
.trigger = ROW, .type = GRUNT, .behavior = STATIC, .fired = FALSE, .px = 5, .py = 10, 
.strafe = 10, .trigger_time=280, .aimed = FALSE
    },
    [16] ={
.trigger = ROW, .type = GRUNT, .behavior = STRAFE_VERTICAL, .fired = FALSE, .px = 85, .py = 10, 
.strafe = 11, .trigger_time=290, .aimed = FALSE
    },
    [17] ={
.trigger = ROW, .type = GRUNT, .behavior = STRAFE_VERTICAL, .fired = FALSE, .px = 15, .py = 10, 
.strafe = 10, .trigger_time=290, .aimed = FALSE
    },
    [18] ={
.trigger = ROW, .type = GRUNT, .behavior = MOVEHORIZONTALLY, .fired = FALSE, .px = 30, .py = 3, 
.strafe = 20, .trigger_time=350, .aimed = FALSE
    },
    [19] ={
.trigger = ROW, .type = GRUNT, .behavior = MOVEHORIZONTALLY, .fired = FALSE, .px = 20, .py = 3, 
.strafe = 20, .trigger_time=350, .aimed = FALSE
    },
    [20] ={
.trigger = ROW, .type = GRUNT, .behavior = MOVEHORIZONTALLY, .fired = FALSE, .px = 10, .py = 3, 
.strafe = 20, .trigger_time=350, .aimed = FALSE
    },
    [21] ={
.trigger = ROW, .type = GRUNT, .behavior = MOVEHORIZONTALLY, .fired = FALSE, .px = 1, .py = 3, 
.strafe = 20, .trigger_time=350, .aimed = FALSE
    },
    [22] ={
.trigger = ROW, .type = RAPIDFIRE, .behavior = STATIC, .fired = FALSE, .px = 40, .py = 3, 
.strafe = 20, .trigger_time=410, .aimed = TRUE
    },
    [23] ={
.trigger = ROW, .type = RAPIDFIRE, .behavior = STATIC, .fired = FALSE, .px = 60, .py = 3, 
.strafe = 20, .trigger_time=410, .aimed = TRUE
    },
    [24] ={
.trigger = ROW, .type = RAPIDFIRE, .behavior = MOVEHORIZONTALLY, .fired = FALSE, .px = 10, .py = 2, 
.strafe = 20, .trigger_time=490, .aimed = FALSE
    },
    [25] ={
.trigger = ROW, .type = RAPIDFIRE, .behavior = MOVEHORIZONTALLY, .fired = FALSE, .px = 6, .py = 2, 
.strafe = 20, .trigger_time=490, .aimed = FALSE
    },
    [26] ={
.trigger = ROW, .type = BOMBER, .behavior = STATIC, .fired = FALSE, .px = 55, .py = 3, 
.strafe = 20, .trigger_time=550, .aimed = FALSE
    },
    [27] ={
.trigger = ROW, .type = BOMBER, .behavior = MOVEHORIZONTALLY, .fired = FALSE, .px = 3, .py = 1, 
.strafe = 20, .trigger_time=600, .aimed = FALSE
    },
    [28] ={
.trigger = ROW, .type = RAPIDFIRE, .behavior = MOVEHORIZONTALLY, .fired = FALSE, .px = 1, .py = 1, 
.strafe = 20, .trigger_time=600, .aimed = FALSE
    },
    [29] ={
.trigger = ROW, .type = RAPIDFIRE, .behavior = MOVEHORIZONTALLY, .fired = FALSE, .px = 2, .py = 1, 
.strafe = 20, .trigger_time=600, .aimed = FALSE
    },
    [30] ={
.trigger = ROW, .type = RAPIDFIRE, .behavior = MOVEHORIZONTALLY, .fired = FALSE, .px = 4, .py = 1, 
.strafe = 20, .trigger_time=600, .aimed = FALSE
    },
    [31] ={
.trigger = ROW, .type = RAPIDFIRE, .behavior = MOVEHORIZONTALLY, .fired = FALSE, .px = 5, .py = 1, 
.strafe = 20, .trigger_time=600, .aimed = FALSE
    },
    [32] ={
.trigger = ROW, .type = RAPIDFIRE, .behavior = MOVEVERTICALLY, .fired = FALSE, .px = 10, .py = 1, 
.strafe = 20, .trigger_time=660, .aimed = TRUE
    },
    [33] ={
.trigger = ROW, .type = RAPIDFIRE, .behavior = MOVEVERTICALLY, .fired = FALSE, .px = 90, .py = 1, 
.strafe = 20, .trigger_time=660, .aimed = TRUE
    },
    [34] ={
.trigger = ROW, .type = RAPIDFIRE, .behavior = MOVEHORIZONTALLY, .fired = FALSE, .px = 5, .py = 1, 
.strafe = 20, .trigger_time=660, .aimed = TRUE
    },
}; */
spawn_entry spawn_table_1[]={

// ================= PHASE 1: Movement & basic dodging (rows 20-140) =================
// Static, unaimed grunts only. Teaches "bullets exist" with zero real pressure.

{.trigger = ROW, .type = GRUNT, .behavior = STATIC, .fired = FALSE,
 .px = 20, .py = 2, .strafe = 0, .trigger_time = 20, .aimed = FALSE},

{.trigger = ROW, .type = GRUNT, .behavior = STATIC, .fired = FALSE,
 .px = 35, .py = 2, .strafe = 0, .trigger_time = 45, .aimed = FALSE},

// First moving enemy - horizontal sweep, still no aim
{.trigger = ROW, .type = GRUNT, .behavior = MOVEHORIZONTALLY, .fired = FALSE,
 .px = 5, .py = 3, .strafe = 0, .trigger_time = 75, .aimed = FALSE},

{.trigger = ROW, .type = GRUNT, .behavior = STATIC, .fired = FALSE,
 .px = 15, .py = 2, .strafe = 0, .trigger_time = 100, .aimed = FALSE},

{.trigger = ROW, .type = GRUNT, .behavior = MOVEVERTICALLY, .fired = FALSE,
 .px = 30, .py = 0, .strafe = 0, .trigger_time = 100, .aimed = FALSE},

// ================= PHASE 2: Aimed fire introduced (rows 170-280) =================

{.trigger = ROW, .type = GRUNT, .behavior = STATIC, .fired = FALSE,
 .px = 25, .py = 2, .strafe = 0, .trigger_time = 170, .aimed = TRUE},

{.trigger = ROW, .type = GRUNT, .behavior = STATIC, .fired = FALSE,
 .px = 10, .py = 2, .strafe = 0, .trigger_time = 195, .aimed = TRUE},

{.trigger = ROW, .type = GRUNT, .behavior = MOVEHORIZONTALLY, .fired = FALSE,
 .px = 45, .py = 3, .strafe = 0, .trigger_time = 220, .aimed = FALSE},

{.trigger = ROW, .type = GRUNT, .behavior = MOVEHORIZONTALLY, .fired = FALSE,
 .px = 5, .py = 4, .strafe = 0, .trigger_time = 220, .aimed = FALSE},

{.trigger = ROW, .type = GRUNT, .behavior = STATIC, .fired = FALSE,
 .px = 30, .py = 2, .strafe = 0, .trigger_time = 250, .aimed = TRUE},

{.trigger = ROW, .type = GRUNT, .behavior = MOVEVERTICALLY, .fired = FALSE,
 .px = 15, .py = 0, .strafe = 0, .trigger_time = 280, .aimed = FALSE},

{.trigger = ROW, .type = GRUNT, .behavior = MOVEVERTICALLY, .fired = FALSE,
 .px = 35, .py = 0, .strafe = 0, .trigger_time = 280, .aimed = FALSE},

// ================= PHASE 3: Rapidfire introduced (rows 330-450) =================

{.trigger = ROW, .type = RAPIDFIRE, .behavior = STATIC, .fired = FALSE,
 .px = 20, .py = 2, .strafe = 0, .trigger_time = 330, .aimed = FALSE},

{.trigger = ROW, .type = GRUNT, .behavior = STATIC, .fired = FALSE,
 .px = 10, .py = 2, .strafe = 0, .trigger_time = 330, .aimed = TRUE},

{.trigger = ROW, .type = RAPIDFIRE, .behavior = MOVEHORIZONTALLY, .fired = FALSE,
 .px = 5, .py = 3, .strafe = 0, .trigger_time = 365, .aimed = FALSE},

{.trigger = ROW, .type = GRUNT, .behavior = MOVEVERTICALLY, .fired = FALSE,
 .px = 40, .py = 0, .strafe = 0, .trigger_time = 365, .aimed = FALSE},

{.trigger = ROW, .type = RAPIDFIRE, .behavior = STRAFE_HORIZONTAL, .fired = FALSE,
 .px = 25, .py = 2, .strafe = 10, .trigger_time = 400, .aimed = FALSE},

{.trigger = ROW, .type = GRUNT, .behavior = STATIC, .fired = FALSE,
 .px = 15, .py = 2, .strafe = 0, .trigger_time = 400, .aimed = TRUE},

{.trigger = ROW, .type = GRUNT, .behavior = STATIC, .fired = FALSE,
 .px = 35, .py = 2, .strafe = 0, .trigger_time = 400, .aimed = TRUE},

{.trigger = ROW, .type = RAPIDFIRE, .behavior = STRAFE_VERTICAL, .fired = FALSE,
 .px = 10, .py = 1, .strafe = 8, .trigger_time = 450, .aimed = FALSE},

// ================= PHASE 4: First bomber + mixed pressure (rows 500-620) =================

{.trigger = ROW, .type = BOMBER, .behavior = STATIC, .fired = FALSE,
 .px = 25, .py = 2, .strafe = 0, .trigger_time = 500, .aimed = FALSE},

{.trigger = ROW, .type = GRUNT, .behavior = MOVEHORIZONTALLY, .fired = FALSE,
 .px = 5, .py = 3, .strafe = 0, .trigger_time = 500, .aimed = FALSE},

{.trigger = ROW, .type = GRUNT, .behavior = MOVEHORIZONTALLY, .fired = FALSE,
 .px = 45, .py = 4, .strafe = 0, .trigger_time = 530, .aimed = FALSE},

{.trigger = ROW, .type = RAPIDFIRE, .behavior = STATIC, .fired = FALSE,
 .px = 15, .py = 2, .strafe = 0, .trigger_time = 560, .aimed = TRUE},

{.trigger = ROW, .type = RAPIDFIRE, .behavior = STATIC, .fired = FALSE,
 .px = 30, .py = 2, .strafe = 0, .trigger_time = 560, .aimed = TRUE},

{.trigger = ROW, .type = GRUNT, .behavior = MOVEVERTICALLY, .fired = FALSE,
 .px = 20, .py = 0, .strafe = 0, .trigger_time = 590, .aimed = FALSE},

{.trigger = ROW, .type = GRUNT, .behavior = MOVEVERTICALLY, .fired = FALSE,
 .px = 30, .py = 0, .strafe = 0, .trigger_time = 590, .aimed = FALSE},

{.trigger = ROW, .type = BOMBER, .behavior = STRAFE_HORIZONTAL, .fired = FALSE,
 .px = 20, .py = 2, .strafe = 10, .trigger_time = 620, .aimed = FALSE},

// ================= PHASE 5: Full remix - everything combined (rows 680-820) =================

{.trigger = ROW, .type = GRUNT, .behavior = STATIC, .fired = FALSE,
 .px = 10, .py = 2, .strafe = 0, .trigger_time = 680, .aimed = TRUE},

{.trigger = ROW, .type = RAPIDFIRE, .behavior = MOVEHORIZONTALLY, .fired = FALSE,
 .px = 5, .py = 3, .strafe = 0, .trigger_time = 680, .aimed = FALSE},

{.trigger = ROW, .type = GRUNT, .behavior = MOVEVERTICALLY, .fired = FALSE,
 .px = 40, .py = 0, .strafe = 0, .trigger_time = 710, .aimed = FALSE},

{.trigger = ROW, .type = RAPIDFIRE, .behavior = STRAFE_HORIZONTAL, .fired = FALSE,
 .px = 25, .py = 2, .strafe = 10, .trigger_time = 740, .aimed = FALSE},

{.trigger = ROW, .type = GRUNT, .behavior = STATIC, .fired = FALSE,
 .px = 15, .py = 2, .strafe = 0, .trigger_time = 740, .aimed = TRUE},

{.trigger = ROW, .type = BOMBER, .behavior = STATIC, .fired = FALSE,
 .px = 30, .py = 2, .strafe = 0, .trigger_time = 770, .aimed = FALSE},

{.trigger = ROW, .type = GRUNT, .behavior = MOVEHORIZONTALLY, .fired = FALSE,
 .px = 45, .py = 4, .strafe = 0, .trigger_time = 800, .aimed = FALSE},

{.trigger = ROW, .type = GRUNT, .behavior = MOVEHORIZONTALLY, .fired = FALSE,
 .px = 5, .py = 4, .strafe = 0, .trigger_time = 800, .aimed = FALSE},

{.trigger = ROW, .type = RAPIDFIRE, .behavior = STATIC, .fired = FALSE,
 .px = 20, .py = 2, .strafe = 0, .trigger_time = 820, .aimed = TRUE},

// ================= PHASE 6: Final gauntlet before the boss (rows 880-1020) =================

{.trigger = ROW, .type = RAPIDFIRE, .behavior = STRAFE_VERTICAL, .fired = FALSE,
 .px = 15, .py = 1, .strafe = 8, .trigger_time = 880, .aimed = FALSE},

{.trigger = ROW, .type = GRUNT, .behavior = STATIC, .fired = FALSE,
 .px = 25, .py = 2, .strafe = 0, .trigger_time = 880, .aimed = TRUE},

{.trigger = ROW, .type = GRUNT, .behavior = STATIC, .fired = FALSE,
 .px = 35, .py = 2, .strafe = 0, .trigger_time = 880, .aimed = TRUE},

{.trigger = ROW, .type = BOMBER, .behavior = STRAFE_VERTICAL, .fired = FALSE,
 .px = 25, .py = 1, .strafe = 8, .trigger_time = 920, .aimed = FALSE},

{.trigger = ROW, .type = GRUNT, .behavior = MOVEVERTICALLY, .fired = FALSE,
 .px = 10, .py = 0, .strafe = 0, .trigger_time = 950, .aimed = FALSE},

{.trigger = ROW, .type = GRUNT, .behavior = MOVEVERTICALLY, .fired = FALSE,
 .px = 40, .py = 0, .strafe = 0, .trigger_time = 950, .aimed = FALSE},

{.trigger = ROW, .type = RAPIDFIRE, .behavior = STATIC, .fired = FALSE,
 .px = 15, .py = 2, .strafe = 0, .trigger_time = 980, .aimed = TRUE},

{.trigger = ROW, .type = RAPIDFIRE, .behavior = STATIC, .fired = FALSE,
 .px = 30, .py = 2, .strafe = 0, .trigger_time = 980, .aimed = TRUE},

{.trigger = ROW, .type = GRUNT, .behavior = MOVEHORIZONTALLY, .fired = FALSE,
 .px = 5, .py = 3, .strafe = 0, .trigger_time = 1020, .aimed = FALSE},

{.trigger = ROW, .type = GRUNT, .behavior = MOVEHORIZONTALLY, .fired = FALSE,
 .px = 45, .py = 3, .strafe = 0, .trigger_time = 1020, .aimed = FALSE},

// ================= Breather before the boss (rows 1020-1200) =================
// Deliberately empty - lets the player catch their breath and clear the field
// before the trigger_time = 1200 carrier boss spawn below.

// ================= BOSS =================

{.trigger = ROW, .type = CARRIER_BOSS, .behavior = CARRIER_SPECIAL, .fired = FALSE,
 .px = 50, .py = 6, .strafe = 0, .trigger_time = 1200, .aimed = TRUE},

};
const int spawn_table_1_count = sizeof(spawn_table_1) / sizeof(spawn_table_1[0]);
spawn_entry spawn_table_2[]={
    [0] ={
.trigger = ROW, .type = FRIGATE1, .behavior = FRIGATE1_SPECIAL, .fired = FALSE, .px = 60, .py = 5, 
.strafe = 0, .trigger_time=10, .aimed = FALSE
    },
    [1] ={
.trigger = ROW, .type = FRIGATE2, .behavior = FRIGATE2_SPECIAL, .fired = FALSE, .px = 40, .py = 6, 
.strafe = 0, .trigger_time=10, .aimed = FALSE
    }
};
const int spawn_table_2_count = sizeof(spawn_table_2) / sizeof(spawn_table_2[0]);