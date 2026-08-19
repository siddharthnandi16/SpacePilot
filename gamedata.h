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
typedef enum trigger{ROW, TICK} TriggerType; //Stores whether an event is triggered by rows_scrolled or ticks that have passed
typedef enum type{ GRUNT, RAPIDFIRE, LASER, BOMBER, HUNTER, JET } EnemyType;
typedef enum state{INACTIVE, DEAD, ALIVE, DYING } EnemyState;
typedef enum behavior{ STATIC, MOVEHORIZONTALLY, MOVEVERTICALLY, STRAFE_HORIZONTAL, STRAFE_VERTICAL, HUNT_PLAYER, ZIGZAG } EnemyBehavior;
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
int age; //Increments every frame, determines some enemy behaviors
float anchor_px, anchor_py; //Sets an "anchor point" for strafing enemies
float strafe; //Sets how far a strafing enemy is willing to go from their anchor point
float old_px, old_py; //Stores old positions of enemy for purpose of drawing
}Enemy;
extern Enemy enemies[];
typedef enum proj_type{BULLET,LASER,BOMB,MISSILE,PLASMA,EMP,CHAINLIGHTNING}ProjType;
typedef enum proj_state{NORMAL,SPENT,EXPLODING}ProjState;
//This struct stores data on the projectile
typedef struct Projectile{
    float px,py;
    float dx,dy;
    char symbol;
    int width, height;
    int age; //Used for bomb detionation timers
    int pierce; //Tells you how many enemies a projectile can pierce before being spent
    float strafe; //Used for special bullets that travel in sine-wave pattern
    float turn_rate; //Used for homing projectiles
    ProjType type; //Used for storing the type of weapon this is 
    ProjState state;
}Projectile;
//This struct defines the behavior of weapons which fire projectiles
typedef enum modes{REGULAR, BURST_FIRE, RAPID_FIRE, SUPERCHARGE}FireModes;
typedef struct WeaponType{
    int cooldown_frames;
    int number; //Number of projectiles fired
    float angle; //Angle at which projectiles are fired in radians. 90 for standard weapons, only deviates from that for secondary shots of weapons that fire multiple projectiles at one
    ProjType type;
    FireModes modes;
}WeaponType;
#endif