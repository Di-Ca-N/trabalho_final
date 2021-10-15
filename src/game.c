#include "game.h"
#include <stdio.h>

// Create a new game
Game newGame() {
    // Static map. Must be replaced with a "loadMap" call after it is implemented
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
        
        .dFramePosition = {0, 0},
        .dFrameSpeed = {0, 0},
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
    printf("oi\n");
    switch (action) {
        case ACTION_RIGHT:
            game.dave.speed.x = 4 * time;
            break;
        case ACTION_LEFT:
            game.dave.speed.x = -4 * time;
            break;
        case ACTION_RELEASE_RIGHT:
        case ACTION_RELEASE_LEFT:
            game.dave.speed.x = 0;
            break;
        default:
            break;
    }
    printf("Nova velocidade do Dave: %f %f\n", game.dave.speed.x, game.dave.speed.y);
    return game;
}

Game updateGame(Game game, double time) {
    time = time * 2;
    printf("Nova velocidade do Dave: %f %f\n", game.dave.speed.x, game.dave.speed.y);
    game.dave.position.x += game.dave.speed.x;
    printf("Nova posição do Dave %f %f\n", game.dave.position.x, game.dave.position.y);
    return game;
}