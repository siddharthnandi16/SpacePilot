#ifndef  SPAWN_H
#define SPAWN_H
typedef struct {
TriggerType trigger;
EnemyType type;
EnemyBehavior behavior;
 //Stores whether the spawns has already occured
 bool fired;
float px;
float py;
float strafe;
int trigger_time; 
}spawn_entry;
extern spawn_entry spawn_table_1[];
#endif