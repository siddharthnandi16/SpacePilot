#ifndef GAMEDATA_H
#define GAMEDATA_H

// This header file stores data about the game's current state
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
#define MAX_TILE_HEIGHT 8 //Max height of multi-tile enemies
#define MAX_TILE_WIDTH  40 //Max width of multi-tile enemies
typedef struct TileLayout {
    int width, height;                          // Dimensions of the shape
    const char *glyph_rows[MAX_TILE_HEIGHT];     // ASCII art, one string per row
    const int  *color_rows[MAX_TILE_HEIGHT];     // Parallel color_pair IDs, one int array per row
} TileLayout;
typedef enum type{ GRUNT, RAPIDFIRE, LASER, BOMBER, HUNTER, JET } EnemyType;
typedef enum state{INACTIVE, DEAD, ALIVE, DYING } EnemyState;
typedef enum behavior{ STATIC, MOVEHORIZONTALLY, MOVEVERTICALLY, HUNT_PLAYER, ZIGZAG } EnemyBehavior;
typedef struct Enemy{
float px, py; //Stores current position
float dx, dy; //Stores the enemy's speed
int hp; //Stores the enemy's HP value. If this is zero, its state changes to dead
char symbol; //Stores what ASCII glyph the enemy is represented by
int width, height; //Stores the width and height of the enemy's bounding box
int cooldown_frames; //Controls rate of fire
EnemyType type;
EnemyState state;
EnemyBehavior behavior;
const TileLayout *shape; //Shape of enemy. Is always NULL for single-tile enemies
}Enemy;
extern Enemy enemies[];
#endif