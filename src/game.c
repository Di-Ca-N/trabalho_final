#include "game.h"
#include <stdio.h>
#include <math.h>

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
    };

    return game;
}

Game handleAction(Game game, Action action, double time) {
    switch (action) {
    case ACTION_RIGHT:
        game.dave.speed.x = WALKING_X_SPEED * time;
        break;
    case ACTION_LEFT:
        game.dave.speed.x = -WALKING_X_SPEED * time;
        break;
    case ACTION_RELEASE_RIGHT:
    case ACTION_RELEASE_LEFT:
        game.dave.speed.x = 0;
        break;
    case ACTION_UP:
        if (!game.dave.jumping)
        {
            game.dave.speed.y = -JUMP_INITIAL_SPEED * time;
            game.dave.jumping = true;
        }
        break;
    default:
        break;
    }

    return game;
}

char getStagePosition(Map map, float x, float y) {
    return map.stage[(int) y][(int) x];
}

Game updateGame(Game game, double time) {
    int offset_x = game.dave.speed.x > 0;

    float nextX = game.dave.position.x + game.dave.speed.x + offset_x;
    float currentY = game.dave.position.y;
    float yCeil = ceil(game.dave.position.y);

    char next_position_x = getStagePosition(game.map, nextX, currentY);
    char next_position_x_d = getStagePosition(game.map, nextX, yCeil);

    if (next_position_x != 'x' && next_position_x_d != 'x') {
        game.dave.position.x += game.dave.speed.x;
    } else {
        if (offset_x) {
            game.dave.position.x = ceil(game.dave.position.x);
        } else {
            game.dave.position.x = (int) game.dave.position.x;
        }
    }

    int offset_y = game.dave.speed.y > 0;

    float nextY = game.dave.position.y + game.dave.speed.y + offset_y;
    float currentX = game.dave.position.x;    
    float xCeil = ceil(game.dave.position.x);

    char next_position_y = getStagePosition(game.map, currentX, nextY);
    char next_position_y_r = getStagePosition(game.map,xCeil, nextY);


    if (next_position_y != 'x' && next_position_y_r != 'x') {
        game.dave.position.y += game.dave.speed.y;
    } else {
        if (offset_y) {
            game.dave.position.y = ceil(game.dave.position.y);
        } else {
            game.dave.position.y = (int) game.dave.position.y;
        }
    }

    float belowDave = game.dave.position.y + game.dave.speed.y + 1;
    char stop_y_below = getStagePosition(game.map, currentX, belowDave);
    char stop_y_below_r = getStagePosition(game.map, xCeil, belowDave);

    game.dave.speed.y += GRAVITY * time;
    if (stop_y_below == 'x' || stop_y_below_r == 'x') {
        game.dave.speed.y = 0;
        game.dave.jumping = false;
    }

    return game;
}

