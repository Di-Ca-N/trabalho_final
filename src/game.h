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
    Vector2 velocity;

    // Remaining lives
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

    // Indicate game over
    bool gameOver;

    // Current player score
    int score;

    // Current level number
    int level;

    // Indicate when to load the next level
    bool nextStage;
} Game;


// Recognized game actions. Defined to decouple input from game actions
typedef enum {
    ACTION_UP = 1, ACTION_DOWN, ACTION_LEFT, ACTION_RIGHT,
    ACTION_RELEASE_UP, ACTION_RELEASE_DOWN, 
    ACTION_RELEASE_RIGHT, ACTION_RELEASE_LEFT,
    ACTION_YES, ACTION_NO, ACTION_SPACE,
} Action;

// ==== FUNCTIONS ====
Game newGame(Map map);                         // Create a new game using the given map
void handleAction(Game* game, Action action);  // Update game state according to actions
void updateGame(Game* game, double timeDelta); // Apply updates on game
void loadNextStage(Game* game, Map map);       // Load the next stage
void releaseAllActions(Game* game);            // Release all movement actions

#endif
