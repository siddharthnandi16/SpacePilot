/* This is a vertical scrolling bullet hell game that uses ASCII graphics. The gameplay is divded 
into stages. The player can move freely within the screen boundaries.
 During each stage the player faces many enemies who shoot bullets at them. There are two
minibosses and one final boss in each stage. 
Getting hit by a bullet causes the player to lose a life.
If all lives are lost, you get a game over and have to start over.
RED= ENEMY, YELLOW= BULLET, GREEN= PLAYER, BLUE=POWER-UPs
Planned additional features: Music, Power-Ups, unlockable upgrades, screen-clearing bombs,
 multiple playable characters with different abilities, sound effects, TTS Voice acting  */
#include <stdbool.h>
#include <stdio.h>
#include <pdcurses.h>
#include <windows.h>
#include <time.h>
#include <mmsystem.h>
#include "titlescreen.h"
#include "gamedata.h"
#include "movement.h"
#include "level.h"
#include "window.h"
#include "enemy.h"
#include "spawn.h"
#include "sound.h"
#include "dialogue.h"
#include "projectile.h"
#include "collision.h"
#include "hud.h"
#include "miniaudio.h"

int game_over =0; //1= true, 0=false
int unsigned long tick=0;
int spawn_table_1_count;
//This function sets the player's current movement speed to their top speed
void setplayermovement(struct Player *player){
player->dx = player->vx;
player->dy = player->vy;
}
int gameloop(Player *player, int max_x, int max_y, GameMode game_mode){
    //spawn_enemy(GRUNT, STATIC, 10, 10, 10); Debug code to test enemy spawning
    while(quit != 1 && game_over != 1){
    tick++;
    ma_sound_start(&loaded_sounds[Level_1]);
    handle_mute_toggle();
    erase_enemies(enemies);
    erase_projectiles(projectiles);
    scrollanddraw(&old_screen_px, &old_screen_py);
    getmaxyx(stdscr, max_y, max_x);
    update_playfield_offset(max_x,max_y);
    draw_playfield_border();
    move_player(player);
    fire_player(player);
    move_projectiles(projectiles, max_x, max_y);
    move_enemy(enemies, player, max_x, max_y);
    fire_enemies(enemies);
    render_enemies(enemies);
    render_projectiles(projectiles);
    switch(game_mode) {
    case STORY_MODE:
        level(&level_1);
        break;
    case ENDLESS_MODE:
    //Commented out as it is not not yet implemented
    endless_level();  
        break;
    default:
        break;
}
    Check_Collisions(player, enemies, projectiles);
    if (player->lives <= 0 || quit == 1){
    ma_sound_stop(&loaded_sounds[Level_1]);
        game_over=1;
        return 0;
    }
    drawHUD(player);
    refresh();
    napms(34); //Controls frame rate and refresh rate
    }
    return 0;
}
int seed; //Variable that stores the RNG seed. Used for various rng calls
//Function to reset all values to their defaults
void reset_all(int max_x, int max_y) {
    player = player_backup;
    player.lives = 5;
    game_over = 0; 
    quit = 0;
    memcpy(enemies, enemies_backup, sizeof(enemies_backup));
    memcpy(projectiles, projectiles_backup, sizeof(projectiles_backup));
    for (int i = 0; i < level_1.spawn_count; i++) {
        spawn_table_1[i].fired = FALSE;
    }
    
    // Reset dialogue tables
    for (int i = 0; i < level_1.dialogue_count; i++) {
        dialogue_table_1[i].fired = FALSE;
    }
    
    // Reset sound tables
    for (int i = 0; i < level_1.sound_count; i++) {
        sound_table_1[i].fired = FALSE;
    }
    spawn_tick = 0;
     fprintf(stderr, "Before update: offset_x=%d, offset_y=%d\n", offset_x, offset_y);
update_playfield_offset(max_x,max_y);
fprintf(stderr, "After update: offset_x=%d, offset_y=%d\n", offset_x, offset_y);
old_screen_py =-1;
old_screen_px= -1;
}
int main(){    
     srand((unsigned)time(NULL));
    //Debug function used to check whether consoles resizing is working properly
// forceConsoleSize_debug(100,30);
initscr();
forceConsoleSize(100,30);
int max_x, max_y;
getmaxyx(stdscr, max_y, max_x);
scrollok(stdscr, TRUE);
curs_set(0);
noecho();
syncConsoleBufferToWindow();
resize_term(0,0);
touchwin(stdscr);
 start_color();
 #define AMBER_COLOR  8
 #define STEEL_GRAY_COLOR  9
#define ACID_GREEN_COLOR  10
#define PURPLE_COLOR      11
#define CRT_BG 12
#define CRT_GREEN 13
init_color(AMBER_COLOR, 1000, 690, 0);
init_color(STEEL_GRAY_COLOR, 541, 608, 659);
    init_color(ACID_GREEN_COLOR, 651, 1000, 0);
    init_color(PURPLE_COLOR, 690, 361, 1000);
    init_color(CRT_BG, 0, 45, 10);       // darker, flatter green-black
init_color(CRT_GREEN, 282, 910, 416);
    init_pair(1, COLOR_GREEN,COLOR_BLACK); //Player
    init_pair(2, COLOR_RED, COLOR_BLACK); //Enemies
    init_pair(3, COLOR_YELLOW, COLOR_BLACK); //Enemy projectiles
    init_pair(4, COLOR_CYAN, COLOR_BLACK); //Player projectiles
    init_pair(5, COLOR_WHITE, COLOR_BLACK); //Background objects
    init_pair(6, AMBER_COLOR, COLOR_BLACK); //Color for HUD
    init_pair(7, STEEL_GRAY_COLOR, COLOR_BLACK); //Used for borders
    init_pair(8, ACID_GREEN_COLOR, COLOR_BLACK);
    init_pair(9,     PURPLE_COLOR,     COLOR_BLACK);
    init_pair(10, CRT_GREEN, CRT_BG); //Colors for future dialogue screen
    
refresh();
keypad(stdscr, TRUE);
//drawTitleScreen();
setplayermovement(&player);
player.px = PLAYFIELD_W/2, player.py = (PLAYFIELD_H)/3*2;
getmaxyx(stdscr, max_y, max_x);
    update_playfield_offset(max_x,max_y);
refresh();
init_audio();
InitialiseSoundEffects(loaded_sounds);
//Placeholder from old audio system, now superseded by miniaudio
//PlaySoundA("Mars.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
 GameMode game_mode = drawTitleScreen();
 erase();
    while(game_mode != MODE_QUIT){
switch(game_mode){
case STORY_MODE:
erase();
gameloop(&player, max_x, max_y, STORY_MODE);
break;
case ENDLESS_MODE:
erase();
gameloop(&player, max_x, max_y, ENDLESS_MODE);
break;
//Placeholder case for unimplemented feature
case HIGH_SCORES:
break;
//Placeholder case for unimplemented feature
case MUSIC_ROOM:
break;
default:
 break; 
}
if (game_mode != MODE_QUIT){
    reset_all(max_x, max_y);
     game_mode = drawTitleScreen();   
}
    }
    
    
    endwin();
    return 0;
}