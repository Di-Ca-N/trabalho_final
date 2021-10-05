#include "game.h"

// Create a new game
Game newGame() {
    // Static map. Must be replaced with a "loadMap" call after it is implemented
    Map map = {
        .stage = {
            "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
            "x                                                                          T                   x",
            "x    J                                                                                         x",
            "x    x          @                                                                              x",
            "x        xxx    x                                                                              x",
            "x                   xxxxxxxxxxxxxxx                                                            x",
            "x                                         $                                                    x",
            "x                                     xxxxxxxxx                                                x",
            "x              #               !                                                               x",
            "x             xxx          xxxxxxxxx                                                           x",
            "x                     !                                                                     %%  x",
            "x        xxx         xxx            xxxxxxxxx                  FFFFFFFFFFFFFFFFFFFFFFFFFFF     x",
            "x  O                                             xxxxxx        FFFFFFFFFFFFFFFFFFFFFFFFFFF     x",
            "x  D                       AAAAAAAAAAAAAAA                 !   FFFFFFFFFFFFFFFFFFFFFFFFFFF  P  x",
            "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
        },
        .daveStart = {13, 3},
        .height = 15,
        .width = 96,
    };

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
