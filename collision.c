#include <pdcurses.h>
#include <math.h>
#include "gamedata.h"
#include  "enemy.h"
#include "projectile.h"
#define MAX_ENEMIES 100
#define MAX_PROJECTILES 2000
int Check_Collisions(Player *player, Enemy *enemies, Projectile *projectiles){
//First loop for enemy-projectile collisions. Enemies only collide with player projectiles
for (int i = 0; i < MAX_ENEMIES; i++){
    for (int p = 0; p < MAX_PROJECTILES; p++){
        if (projectiles[p].player_owned == TRUE && projectiles[p].state != SPENT && enemies[i].state == ALIVE){
  if (enemies[i].shape == NULL){
    //Handling non-laser projectile types
    if(projectiles[i].type != LASER){
int y_min = (int)fminf(projectiles[p].old_py, projectiles[p].py);
int y_max = (int)fmaxf(projectiles[p].old_py, projectiles[p].py);
int x_min = (int)fminf(projectiles[p].old_px, projectiles[p].px);
int x_max = (int)fmaxf(projectiles[p].old_px, projectiles[p].px);
if ((int)enemies[i].px == (int)projectiles[p].px &&
    (int)enemies[i].py >= y_min && (int)enemies[i].py <= y_max
&& (int)enemies[i].px >= x_min && (int)enemies[i].px <= x_max){
enemies[i].hp = enemies[i].hp - projectiles[p].damage;
projectiles[p].pierce--;
if (projectiles[p].type == BOMB){
    projectiles[p].state = EXPLODING;
}
    }
    
   if(enemies[i].hp <= 0){
enemies[i].state = DEAD;
};
}
//Special code for laser-type projectiles
if(projectiles[p].type == LASER){
if((int)enemies[i].px == (int)projectiles[p].px){
    enemies[i].hp = enemies[i].hp - projectiles[p].damage;
projectiles[p].pierce--;
 if(enemies[i].hp <= 0){
enemies[i].state = DEAD;
};
}
}
}
 //Collision for multi-tile enemies to be added later
}    
}
}
//Second loop for player-projectile collisions
if (player->invuln_frames > 0){player->invuln_frames--;}
for (int p = 0; p < MAX_PROJECTILES; p++){
if (projectiles[p].player_owned == FALSE && projectiles[p].state != SPENT){
   int y_min = (int)fminf(projectiles[p].old_py, projectiles[p].py);
int y_max = (int)fmaxf(projectiles[p].old_py, projectiles[p].py);
int x_min = (int)fminf(projectiles[p].old_px, projectiles[p].px);
int x_max = (int)fmaxf(projectiles[p].old_px, projectiles[p].px);
if(projectiles[p].type == LASER){
if((int)player->px == (int)projectiles[p].px && player->invuln_frames <= 0){
player->lives--;
 player->invuln_frames = 60;  
projectiles[p].pierce--;
}
}
else {
if ((int)player->px == (int)projectiles[p].px &&
    (int)player->py >= y_min && (int)player->py <= y_max
&& (int)player->px >= x_min && (int)player->px <= x_max
&& player->invuln_frames <= 0){
    player->lives--;
    player->invuln_frames = 60;  
    projectiles[p].pierce--;
}
}
}
}
//Third loop for player-enemy collisions
for (int i = 0; i < MAX_ENEMIES; i++){
    if (enemies[i].state == ALIVE){
        if (enemies[i].px == player->px && enemies[i].py == player->py && player->invuln_frames <= 0){
             player->lives--;
    player->invuln_frames = 60; 
        }
    }
}
return 1;
}