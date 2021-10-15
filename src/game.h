/******************************************************
 * game module
 * Main game logic
 ******************************************************/
#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "maps.h"

// ==== CONSTANTS ====
#define GRAVITY 10             // Game gravity
#define WALKING_X_SPEED 8      // Dave's walking speed
#define JUMP_INITIAL_SPEED 30  // Dave's jump impulse
#define FLYING_SPEED 8         // Dave's flying speed (with jetpack)

// ==== TYPEDEFS ====

// Dave representation
typedef struct {
    // Dave position and speed
    Vector2 position;
    Vector2 speed;

    int lives;

    // State flags
    bool jumping;
    bool flying;
    bool gotTrophy;
    bool hasJetpack;

    // Frame update acumulators
    Vector2 dFramePosition;
    Vector2 dFrameSpeed;
} Dave;

// Game representation
typedef struct {
    // Dave and Map representations
    Dave dave;
    Map map;

    // Current player score
    int score;

    // Current stage number
    int stage;
} Game;

// Recognized game actions. Defined to decouple input 
// from game actions
typedef enum {
    ACTION_UP = 1, ACTION_DOWN, ACTION_LEFT, ACTION_RIGHT,
    ACTION_EXIT, ACTION_SAVE, ACTION_STOP, 
    ACTION_RELEASE_UP, ACTION_RELEASE_DOWN, 
    ACTION_RELEASE_RIGHT, ACTION_RELEASE_LEFT,
    ACTION_YES, ACTION_NO,
} Action;

// ==== FUNCTIONS ====
Game newGame();                                            // Create a new game
Game handleAction(Game game, Action action, double time);  // Update game state according to actions
Game updateGame(Game game, double time);                   // Apply updates on game

#endif
