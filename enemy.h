#ifndef ENEMY_H
#define ENEMY_H
int findfreeslot(void);
const Enemy* get_template(EnemyType type);
void spawn_enemy(EnemyType type, EnemyBehavior behavior, float px, float py);
#endif