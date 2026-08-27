#include <pdcurses.h>
#include "gamedata.h"
// This file stores data on players, enemies and bullets
/* struct Player{
    float px, py; //Stores the player's position
    float vx, vy; // Stores the player's standard movement speed
    float dx, dy; //Stores the player's current movement direction and speed
    int alive; //Stores whether the player is alive or dead, 1=alive, 0=dead
    int lives; //Stores the number of lives of the player
    bool hasLasers, hasBombs; // Stores whether the player has access to special weapons
    int fire_rate; //Determines rate of fire
    char symbol;
    bool speed_mode_fast ; //Making this false halves player movement
    bool q_was_down; //Checks whether the speed-toggle was held down last frame and prevents it from activating if it was
  WeaponID weapon_id;
    WeaponID inventory[100]; //Size maximised for debug purposes will be reduced to 10 later 
}; */
// Commented out since it conflicts with the typedef in gamedata.h
//Bool that stores whether the player is moving diagonally
bool moving_diagonally = FALSE;
struct Player player = {
    .px = PLAYFIELD_W/2, .py = (PLAYFIELD_H)/3*2,
    .vx = 2, .vy = 2,
    .dx = 2, .dy = 2,
    .alive = 1,
    .lives = 5,
    .hasLasers = true, .hasBombs = true,
    .fire_rate = 20,
    .symbol = '@',
    .speed_mode_fast = true,
    .q_was_down = false,
    .weapon_id = AUTOPISTOL_ID,
    .inventory = {AUTOPISTOL_ID, MACHINEGUN_ID, LASRIFLE_PLAYER_ID, 
        BOMB_PLAYER_ID, PLASMARIFLE_PLAYER_ID, MISSILE_PLAYER_ID, SHOTGUN_ID, 
        SPIRAL_CANNON_ID, LASERCANNON_ID},
    // For debug purposes, all implemented weapons are given to the player 
    .invuln_frames = 0,
    .score =0
};
//Backup version of player struct. ALWAYS KEEP IT THE SAME AS THE PLAYER STRUCT
struct Player player_backup = {
    .px = PLAYFIELD_W/2, .py = (PLAYFIELD_H/3) * 2,
    .vx = 2, .vy = 2,
    .dx = 2, .dy = 2,
    .alive = 1,
    .lives = 5,
    .hasLasers = true, .hasBombs = true,
    .fire_rate = 20,
    .symbol = '@',
    .speed_mode_fast = true,
    .q_was_down = false,
    .weapon_id = AUTOPISTOL_ID,
    .inventory = {AUTOPISTOL_ID, MACHINEGUN_ID, LASRIFLE_PLAYER_ID, 
        BOMB_PLAYER_ID, PLASMARIFLE_PLAYER_ID, MISSILE_PLAYER_ID,SHOTGUN_ID, 
        SPIRAL_CANNON_ID, LASERCANNON_ID},
    // For debug purpose, all implemented weapons are given to the player 
    .invuln_frames = 0,
    .score = 0
};
BossState state = BOSS_NORMAL;
int boss_state_timer = 0;                
 bool boss_invulnerable = FALSE;               
  
