#include "game.h"

#include <math.h>

// Static functions prototypes, only to be used inside this module
static void moveDave(Game *game, double time);
static void checkInteraction(Game *game);

/**
 * Create a new game using the given map
 *
 * Arguments:
 *     map (Map): Map to be used as the first stage
 */
Game newGame(Map map) {
    // Dave starting representation
    Dave dave = {
        .position = {map.daveStart[1], map.daveStart[0]},
        .velocity = {0, 0},

        .lives = 3,

        .jumping = false,
        .flying = false,
        .gotTrophy = false,
        .hasJetpack = false,
    };

    // New game
    Game game = {
        .map = map,
        .dave = dave,
        .level = 1,
        .score = 0,
        .nextStage = false,
        .gameOver = false,
        .victory = false,
    };

    return game;
}

/**
 * Update the game state based on a single game action.
 * This function only manipulates the velocity of objects based on the
 * action. To update the game object positions, call 'updateGame' after.
 *
 * Arguments:
 *     game (Game): Game to be updated
 *     action (Action): Action to handle
 */
void handleAction(Game *game, Action action) {
    switch (action) {
        // Right and left actions: assign Dave the correct x speed
        // according to its state
        case ACTION_RIGHT:
            if (game->dave.flying) {
                game->dave.velocity.x = FLYING_SPEED;
            } else {
                game->dave.velocity.x = WALKING_X_SPEED;
            }
            break;
        case ACTION_LEFT:
            if (game->dave.flying) {
                game->dave.velocity.x = -FLYING_SPEED;
            } else {
                game->dave.velocity.x = -WALKING_X_SPEED;
            }
            break;

        // Up and down actions: assign Dave the correct y speed
        // according to its state
        case ACTION_UP:
            if (!game->dave.flying) {
                if (!game->dave.jumping) {
                    game->dave.velocity.y = -JUMP_INITIAL_SPEED;
                    game->dave.jumping = true;
                }
            } else {
                game->dave.velocity.y = -FLYING_SPEED;
            }
            break;
        case ACTION_DOWN:
            if (game->dave.flying) {
                game->dave.velocity.y = FLYING_SPEED;
            }
            break;

        // Release actions: update Dave's speed
        case ACTION_RELEASE_RIGHT:
        case ACTION_RELEASE_LEFT:
            game->dave.velocity.x = 0;
            break;
        case ACTION_RELEASE_UP:
        case ACTION_RELEASE_DOWN:
            // Only reset speed if Dave is flying
            if (game->dave.flying) {
                game->dave.velocity.y = 0;
            }
            break;

        // Space action: Activate Jetpack if it was collected
        case ACTION_SPACE:
            if (game->dave.hasJetpack) {
                game->dave.flying = !game->dave.flying;
                game->dave.velocity.y = 0;
            }
            break;

        // Ignore every other action
        default:
            break;
    }
}

/**
 * Update the game objects positions and general game state.
 *
 * Arguments:
 *     game (Game*): Game to be updated
 *     timeDelta (double): Time elapsed since last update
 */
void updateGame(Game *game, double timeDelta) {
    moveDave(game, timeDelta);
    checkInteraction(game);
}

/**
 * Update Dave position based on the current game state
 *
 * Arguments:
 *     game (Game*): Pointer to the game to be updated
 *     timeDelta (double): Time elapsed
 */
static void moveDave(Game *game, double timeDelta) {
    // Dave X Position Update

    // Indicate whether Dave is movind to the right
    int goingRight = game->dave.velocity.x > 0;
    float dx = game->dave.velocity.x * timeDelta;

    float nextX = game->dave.position.x + dx + goingRight;
    float currentY = game->dave.position.y;
    float yCeil = ceil(game->dave.position.y);

    // Objects on the next x position of Dave. It is necessary to check
    // two positions because Dave can be located between two integer
    // y positions
    char next_position_x = getStagePosition(&game->map, nextX, currentY);
    char next_position_x_forward = getStagePosition(&game->map, nextX, yCeil);

    if (next_position_x != WALL && next_position_x_forward != WALL) {
        // If neither position is a wall, update Dave x position
        game->dave.position.x += game->dave.velocity.x * timeDelta;
    } else {
        // Otherwise, correct Dave position in relation to the wall,
        // based on its current movement direction
        if (goingRight) {
            // If he is going to the right, the corrected position is
            // the ceil of the current x position
            game->dave.position.x = ceil(game->dave.position.x);
        } else {
            // If he is going to the left, the corrected position is the
            // floor of the current x position
            game->dave.position.x = floor(game->dave.position.x);
        }
    }

    // Dave Y position update
    int goingDown = game->dave.velocity.y > 0;

    float dy = game->dave.velocity.y * timeDelta;
    float nextY = game->dave.position.y + dy + goingDown;
    float currentX = game->dave.position.x;
    float xCeil = ceil(game->dave.position.x);

    // Objects on the next y position of Dave. It is necessary to check
    // two positions because Dave can be located between two integer
    // x positions
    char next_position_y = getStagePosition(&game->map, currentX, nextY);
    char next_position_y_r = getStagePosition(&game->map, xCeil, nextY);

    // If there is no wall on Dave's path on the Y axis
    if (next_position_y != WALL && next_position_y_r != WALL) {
        // Update Dave Y pos
        game->dave.position.y += game->dave.velocity.y * timeDelta;
    } else {
        // If there is a wall, corrects Dave Y position
        if (goingDown) {
            game->dave.position.y = ceil(game->dave.position.y);
        } else {
            game->dave.position.y = floor(game->dave.position.y);
        }
    }

    // Dave floor interaction
    float belowDave = game->dave.position.y + dy + 1;

    // Objects below Dave. It is necessary to check two positions
    // because Dave can be located between two integer x positions
    char stop_y_below = getStagePosition(&game->map, currentX, belowDave);
    char stop_y_below_r = getStagePosition(&game->map, xCeil, belowDave);

    // If there is a wall below Dave
    if (stop_y_below == WALL || stop_y_below_r == WALL) {
        // Y velocity becomes zero
        game->dave.velocity.y = 0;
        // Reset jump flag (so Dave can jump again)
        game->dave.jumping = false;
    }

    // Apply gravity
    if (!game->dave.flying) {
        game->dave.velocity.y += GRAVITY * timeDelta;
    }
}

/**
 * Process Dave interactions with the level environment
 *
 * Arguments:
 *     game (Game*): Pointer to the Game to be updated
 */
static void checkInteraction(Game *game) {
    // Positions to be checked for collisions
    Vector2 checkPosition[4] = {
        // Current Dave position
        {game->dave.position.x, game->dave.position.y},

        // Positions that Dave spans if its coordinates are not integers
        {ceil(game->dave.position.x), game->dave.position.y},
        {game->dave.position.x, ceil(game->dave.position.y)},
        {ceil(game->dave.position.x), ceil(game->dave.position.y)},
    };
    // Indicate that damage was already processed on the current
    // update. On each update, the damage must be processed only once.
    bool processedDamage = false;

    // For each position to be checked
    for (int i = 0; i < 4; i++) {
        // Get the char on that map position
        char pos = getStagePosition(&game->map, checkPosition[i].x,
                                    checkPosition[i].y);
        // If the position contains
        switch (pos) {
            case WATER:
            case FIRE:
                // If damage was not processed on the current update
                if (!processedDamage) {
                    // Set processed damage flag
                    processedDamage = true;
                    // Dave loses a life
                    game->dave.lives--;

                    // If lives reach zero, it is Game Over
                    if (game->dave.lives == 0) {
                        game->gameOver = true;
                    }

                    // Stops flying
                    game->dave.flying = false;

                    // Return to the starting position
                    game->dave.position.y = game->map.daveStart[0];
                    game->dave.position.x = game->map.daveStart[1];

                    // And loses 500 score
                    game->score -= 500;
                }
                break;

            case JETPACK:
                // Update jetpack flag
                game->dave.hasJetpack = true;
                // Remove it from the map
                clearStagePosition(&game->map, checkPosition[i].x,
                                   checkPosition[i].y);
                break;

            case TROPHY:
                // Update trophy flag
                game->dave.gotTrophy = true;
                // Give Dave 1000 score
                game->score += 1000;
                // Remove it from the map
                clearStagePosition(&game->map, checkPosition[i].x,
                                   checkPosition[i].y);
                break;

            case DOOR:
                // If Dave already have the trophy and the next stage
                // flag is not already marked
                if (game->dave.gotTrophy && !game->nextStage) {
                    // Update the flag and increment the curent level
                    game->nextStage = true;
                    game->level++;
                }
                break;

            // With any other collectible, give the player the
            // correspondent score and remove it from the map
            case SAPHIRE:
                game->score += 100;
                clearStagePosition(&game->map, checkPosition[i].x,
                                   checkPosition[i].y);
                break;
            case AMETHYST:
                game->score += 50;
                clearStagePosition(&game->map, checkPosition[i].x,
                                   checkPosition[i].y);
                break;
            case CROWN:
                game->score += 300;
                clearStagePosition(&game->map, checkPosition[i].x,
                                   checkPosition[i].y);
                break;
            case RUBY:
                game->score += 300;
                clearStagePosition(&game->map, checkPosition[i].x,
                                   checkPosition[i].y);
                break;
            case RING:
                game->score += 200;
                clearStagePosition(&game->map, checkPosition[i].x,
                                   checkPosition[i].y);
                break;
        }
    }
}

/**
 * Load the next map into the game.
 *
 * Arguments:
 *     game (Game*): Pointer to the game to be updated
 *     map (Map): Map to be used in the next stage
 */
void loadNextStage(Game *game, Map map) {
    // Updating the map
    game->map = map;

    // Reseting game state for the next level
    game->dave.gotTrophy = false;
    game->dave.hasJetpack = false;
    game->dave.flying = false;
    game->dave.position.x = game->map.daveStart[1];
    game->dave.position.y = game->map.daveStart[0];
    game->dave.velocity.x = 0;
    game->dave.velocity.y = 0;
    game->nextStage = false;
}

/**
 * Release all game actions. Useful to avoid unwanted moves on saving
 * or pausing the game.
 *
 * Arguments:
 *    game (Game*): Game to be updated
 */
void releaseAllActions(Game *game) {
    handleAction(game, ACTION_RELEASE_DOWN);
    handleAction(game, ACTION_RELEASE_UP);
    handleAction(game, ACTION_RELEASE_LEFT);
    handleAction(game, ACTION_RELEASE_RIGHT);
}