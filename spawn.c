#include <pdcurses.h>
#include  "gamedata.h"
#include "spawn.h"
spawn_entry spawn_table_1[]={
    [0] ={
.trigger = ROW, .type = GRUNT, .behavior = STATIC, .fired = FALSE, .px = 10, .py = 10, .strafe = 0, .trigger_time=0
    }
};