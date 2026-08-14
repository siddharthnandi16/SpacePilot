#ifndef PLAYER_H
#define PLAYER_H
typedef struct Player{
    float px, py; //Stores the player's position
    float vx, vy; // Stores the player's standard movement speed
    float dx, dy; //Stores the player's current movement direction and speed
    int alive; //Stores whether the player is alive or dead, 1=alive, 0=dead
    int lives; //Stores the number of lives of the player
    bool hasLasers, hasBombs; // Stores whether the player has access to special weapons
    int power; // Will affect fire rate later on when upgrades are added, currently unused
    char symbol;
    bool speed_mode_fast ; //Making this false halves player movement
    bool q_was_down; 
    //Checks whether the speed-toggle was held down last frame and prevents it from activating if it was
}Player;
extern Player player;
#endif