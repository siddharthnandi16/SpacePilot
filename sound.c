#include <pdcurses.h>
#include  "gamedata.h"
#include "sound.h"
sound_entry sound_table_1[]={
    [0] ={
.trigger = ROW, .is_song=TRUE, .loop = TRUE, .fired = FALSE, .trigger_time = 0, .sound_effect_id = 0,
    }
};