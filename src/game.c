#include "game.h"
#include <stdio.h>

// Create a new game
Game newGame()
{
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

Game handleAction(Game game, Action action, double time)
{

    switch (action)
    {
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
    case ACTION_UP:
        if (!game.dave.jumping)
        {
            game.dave.speed.y = -30 * time;
            game.dave.jumping = true;
        }
        break;
    default:
        break;
    }

    return game;
}

Game updateGame(Game game, double time)
{

    char next_position_x;
    char next_position_y;
    char stop_y_below;
    int offset_x = game.dave.speed.x > 0;
    int offset_y = game.dave.speed.y > 0;

    next_position_x = game.map.stage[(int)(game.dave.position.y)][(int)(game.dave.position.x + game.dave.speed.x + offset_x)];
    next_position_y = game.map.stage[(int)(game.dave.position.y + game.dave.speed.y + offset_y)][(int)(game.dave.position.x)];
    stop_y_below = game.map.stage[(int)(game.dave.position.y + game.dave.speed.y + 1)][(int)(game.dave.position.x)];

    if (next_position_x != 'x')
    {
        game.dave.position.x += game.dave.speed.x;
    }

    if (next_position_y != 'x')
    {
        game.dave.position.y += game.dave.speed.y;
    }
    if (stop_y_below != 'x')
    {
        game.dave.speed.y += GRAVITY * time;
    } else {
      game.dave.speed.y = 0; 
      game.dave.jumping = false;
      }
    return game;
}