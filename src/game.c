#include "game.h"

// Create a new game
Game newGame() {
    // Static map. Must be replaced with a "loadMap" call after it is implemented
    Map map = loadMap("assets/stages/mapa1.txt");

    // Dave starting representation
    Dave dave = {
        .position = {.x = map.daveStart[0], .y = map.daveStart[1]},
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

// Game handleAction(Game game, Action action, double time) {

// }