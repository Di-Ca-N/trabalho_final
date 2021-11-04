/******************************************************
 * game module
 * Main game logic
 ******************************************************/
#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "maps.h"

// ==== CONSTANTS ====
#define GRAVITY 50             // Game gravity
#define WALKING_X_SPEED 6      // Dave's walking speed
#define JUMP_INITIAL_SPEED 18  // Dave's jump impulse
#define FLYING_SPEED 8         // Dave's flying speed (with jetpack)

// ==== TYPEDEFS ====

// Dave representation
typedef struct {
    // Dave position and speed
    Vector2 position;
    Vector2 speed;

    // Remaining Dave lives
    int lives;

    // State flags
    bool jumping;
    bool flying;
    bool gotTrophy;
    bool hasJetpack;

} Dave;

// Game representation
typedef struct {
    // Dave and Map representations
    Dave dave;
    Map map;

    // Game over flag
    bool gameOver;

    // Next level flag

    bool nextStage;

    // Current player score
    int score;

    // Current level number
    int level;
} Game;

    
// Recognized game actions. Defined to decouple input 
// from game actions
typedef enum {
    ACTION_UP = 1, ACTION_DOWN, ACTION_LEFT, ACTION_RIGHT,
    ACTION_EXIT, ACTION_SAVE, ACTION_STOP, 
    ACTION_RELEASE_UP, ACTION_RELEASE_DOWN, 
    ACTION_RELEASE_RIGHT, ACTION_RELEASE_LEFT,
    ACTION_YES, ACTION_NO,
    ACTION_SPACE,
} Action;

// ==== FUNCTIONS ====
Game newGame();                                // Create a new game
void handleAction(Game* game, Action action);  // Update game state according to actions
void updateGame(Game* game, double timeDelta); // Apply updates on game
void loadNextStage(Game* game);                // Load the next stage

#endif
