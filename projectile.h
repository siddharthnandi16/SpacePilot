#include "gamedata.h"
#ifndef PROJECTILE_H
#define PROJECTILE_H
extern WeaponType autopistol;
extern WeaponType machinegun;
extern WeaponType laserrifle;
extern WeaponType bomblauncher;
extern WeaponType plasmarifle;
extern WeaponType missilelauncher;
extern WeaponType empbomb;
extern WeaponType lightning;
extern WeaponType shotgun;
extern WeaponType lasercannon;
extern WeaponType plasmacannon;
extern WeaponType GRUNT_RIFLE;
extern WeaponType RAPIDFIRE_RIFLE;
extern WeaponType LASER_RIFLE;
extern WeaponType BOMB_ENEMY_WEAPON;
extern WeaponType HUNTER_RIFLE;
void fire_weapon(const WeaponType *weapon, float px, float py, float angle, bool player_owned);
const WeaponType* get_weapon_template(WeaponID weapon_id);
int findfreeprojectileslot(void);
#endif