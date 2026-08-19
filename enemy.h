#ifndef ENEMY_H
#define ENEMY_H
int findfreeslot(void);
const Enemy* get_template(EnemyType type);
void spawn_enemy(EnemyType type, EnemyBehavior behavior, float px, float py, float strafe);
void move_enemy(Enemy *enemies, int max_x, int max_y);
void erase_enemies(Enemy *enemies);
void render_enemies(Enemy *enemies);
#endif