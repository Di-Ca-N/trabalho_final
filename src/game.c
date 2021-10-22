#include "game.h"

#include <math.h>
#include <stdio.h>

void moveDave(Game *game, double time);
void checkInteraction(Game *game);

// Create a new game
Game newGame() {
    // Load first stage map
    Map map = loadMap("assets/stages/mapa1.txt");

    // Dave starting representation
    Dave dave = {
        .position = {map.daveStart[1], map.daveStart[0]},
        .speed = {0, 0},

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
        .stage = 1,
        .score = 0,
        .gameOver = false,
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
 *     time (double): Time elapsed
 */
void handleAction(Game *game, Action action, double time) {
    switch (action) {
        case ACTION_RIGHT:
            if (game->dave.flying) {
                game->dave.speed.x = FLYING_SPEED * time;
            } else {
                game->dave.speed.x = WALKING_X_SPEED * time;
            }
            break;
        case ACTION_LEFT:
            if (game->dave.flying) {
                game->dave.speed.x = -FLYING_SPEED * time;
            } else {
                game->dave.speed.x = -WALKING_X_SPEED * time;
            }
            break;
        case ACTION_RELEASE_RIGHT:
        case ACTION_RELEASE_LEFT:
            game->dave.speed.x = 0;
            break;
        case ACTION_UP:
            if (!game->dave.flying) {
                if (!game->dave.jumping) {
                    game->dave.speed.y = -JUMP_INITIAL_SPEED * time;
                    game->dave.jumping = true;
                }
            } else {
                game->dave.speed.y = -FLYING_SPEED * time;
            }
            break;
        case ACTION_SPACE:
            if (game->dave.hasJetpack) {
                game->dave.flying = !game->dave.flying;
                game->dave.speed.y = 0;
            }
            break;
        case ACTION_DOWN:
            if (game->dave.flying) {
                game->dave.speed.y = FLYING_SPEED * time;
            }
            break;
        case ACTION_RELEASE_UP:
        case ACTION_RELEASE_DOWN:
            if (game->dave.flying) {
                game->dave.speed.y = 0;
            }
            break;
        default:
            break;
    }
}

char getStagePosition(Map *map, float x, float y) {
    return map->stage[(int)y][(int)x];
}

/**
 * Update the game objects positions and general game state.
 *
 * Arguments:
 *     game (Game): Game to be updated
 *     time (double): Time elapsed
 */
void updateGame(Game *game, double time) {
    printf("Score: %d, Jetpack: %d, Vidas: %d, Troféu: %d\n", game->score,
           game->dave.hasJetpack, game->dave.lives, game->dave.gotTrophy);
    moveDave(game, time);
    checkInteraction(game);
}

void moveDave(Game *game, double time) {
    // Dave X Position Update

    // Indicate whether Dave is movind to the right
    int goingRight = game->dave.speed.x > 0;

    float nextX = game->dave.position.x + game->dave.speed.x + goingRight;
    float currentY = game->dave.position.y;
    float yCeil = ceil(game->dave.position.y);

    // Objects on the next x position of Dave. It is necessary to check
    // two positions because Dave can be located between two integer
    // y positions
    char next_position_x = getStagePosition(&game->map, nextX, currentY);
    char next_position_x_forward = getStagePosition(&game->map, nextX, yCeil);

    if (next_position_x != WALL && next_position_x_forward != WALL) {
        // If neither position is a wall, update Dave x position
        game->dave.position.x += game->dave.speed.x;
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
    int goingDown = game->dave.speed.y > 0;

    float nextY = game->dave.position.y + game->dave.speed.y + goingDown;
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
        game->dave.position.y += game->dave.speed.y;
    } else {
        // If there is a wall, corrects Dave Y position
        if (goingDown) {
            game->dave.position.y = ceil(game->dave.position.y);
        } else {
            game->dave.position.y = floor(game->dave.position.y);
        }
    }

    // Dave floor interaction
    float belowDave = game->dave.position.y + game->dave.speed.y + 1;

    // Objects below Dave. It is necessary to check two positions
    // because Dave can be located between two integer x positions
    char stop_y_below = getStagePosition(&game->map, currentX, belowDave);
    char stop_y_below_r = getStagePosition(&game->map, xCeil, belowDave);

    // Apply gravity
    if (!game->dave.flying) {
        game->dave.speed.y += GRAVITY * time;
    }

    // If there is a wall below Dave
    if (stop_y_below == WALL || stop_y_below_r == WALL) {
        // Y speed becomes zero
        game->dave.speed.y = 0;
        // Reset jump flag (so Dave can jump again)
        game->dave.jumping = false;
    }
}

void checkInteraction(Game *game) {
    Vector2 checkPosition[4] = {
        {game->dave.position.x, game->dave.position.y},
        {ceil(game->dave.position.x), game->dave.position.y},
        {game->dave.position.x, ceil(game->dave.position.y)},
        {ceil(game->dave.position.x), ceil(game->dave.position.y)},
    };

    for (int i = 0; i < 4; i++) {
        char pos = getStagePosition(&game->map, checkPosition[i].x,
                                    checkPosition[i].y);
        switch (pos) {
            case WATER:
            case FIRE:
                game->dave.lives--;
                game->dave.flying = false;
                game->dave.position.y = game->map.daveStart[0];
                game->dave.position.x = game->map.daveStart[1];
                game->score -= 500;
                break;
            case JETPACK:
                game->dave.hasJetpack = true;
                game->map
                    .stage[(int)checkPosition[i].y][(int)checkPosition[i].x] =
                    ' ';
                break;
            case TROPHY:
                game->dave.gotTrophy = true;
                game->score += 1000;
                game->map
                    .stage[(int)checkPosition[i].y][(int)checkPosition[i].x] =
                    ' ';
                break;
            case SAPHIRE:
                game->score += 100;
                game->map
                    .stage[(int)checkPosition[i].y][(int)checkPosition[i].x] =
                    ' ';
                break;
            case AMETIST:
                game->score += 50;
                game->map
                    .stage[(int)checkPosition[i].y][(int)checkPosition[i].x] =
                    ' ';
                break;
            case CROWN:
                game->score += 300;
                game->map
                    .stage[(int)checkPosition[i].y][(int)checkPosition[i].x] =
                    ' ';
                break;
            case RUBY:
                game->score += 300;
                game->map
                    .stage[(int)checkPosition[i].y][(int)checkPosition[i].x] =
                    ' ';
                break;
            case RING:
                game->score += 200;
                game->map
                    .stage[(int)checkPosition[i].y][(int)checkPosition[i].x] =
                    ' ';
                break;
        }
    }
}
