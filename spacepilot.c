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
#include <pdcurses.h>
#include <windows.h>
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
int quit = 0; //1= true, 0= false
int unsigned long tick=0;
int spawn_table_1_count;
//This function sets the player's current movement speed to their top speed
void setplayermovement(struct Player *player){
player->dx = player->vx;
player->dy = player->vy;
}
int gameloop(Player *player, int max_x, int max_y){
    //spawn_enemy(GRUNT, STATIC, 10, 10, 10); Debug code to test enemy spawning
    while(1){
        //Debug code to see how fast the function is running
       // a++;
       // printf("%d", a);
    tick++;
    erase_enemies(enemies);
    erase_projectiles(projectiles);
    scrollanddraw();
    getmaxyx(stdscr, max_y, max_x);
    move_player(&player->px, &player->py, player->dy,  player->dx, max_x, max_y, &player->speed_mode_fast, player->vx, player->vy, &player->q_was_down);
    fire_player(player);
    move_projectiles(projectiles, max_x, max_y);
    move_enemy(enemies, max_x, max_y);
    fire_enemies(enemies);
    render_enemies(enemies);
    render_projectiles(projectiles);
    level(&level_1);
    refresh();
    napms(34); //Controls frame rate and refresh rate
    }
    return 0;
}
int seed; //Variable that stores the RNG seed. Used for various rng calls

int main(){    
     
initscr();
int max_x, max_y;
getmaxyx(stdscr, max_y, max_x);
scrollok(stdscr, TRUE);
curs_set(0);
noecho();
syncConsoleBufferToWindow();
resize_term(0,0);
touchwin(stdscr);
 start_color();
    init_pair(1, COLOR_GREEN,COLOR_BLACK); //Player
    init_pair(2, COLOR_RED, COLOR_BLACK); //Enemies
    init_pair(3, COLOR_YELLOW, COLOR_BLACK); //Enemy projectiles
    init_pair(4, COLOR_CYAN, COLOR_BLACK); //Player projectiles
    init_pair(5, COLOR_WHITE, COLOR_BLACK); //Background objects
refresh();
drawTitleScreen(quit);
setplayermovement(&player);
player.px = max_x/2, player.py = max_y/2;
seed = max_x + max_y;
srand(seed);
    refresh();
    erase();
    gameloop(&player, max_x, max_y);
    endwin();
    return 0;
}