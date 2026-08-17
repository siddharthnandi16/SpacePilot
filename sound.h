#ifndef SOUND_H
#define SOUND_H
typedef struct {
TriggerType trigger;
bool is_song; //True for songs, false for sound effects
bool loop; //Determines whether the song will loop or not, TRUE if it loops
bool fired;
int trigger_time; 
int sound_effect_id; //All sounds effects in the game will be given a unique ID
}sound_entry;
extern sound_entry sound_table_1[];
#endif