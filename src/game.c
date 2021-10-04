#include "game.h"

// Create a new game
Game newGame() {
    // Dummy map. Replace with a "loadMap" call after it is done
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

    Game game = {
        .map = map,
        .dave = dave,
        .stage = 1,
        .score = 0,
        .gravity = 10,
    };

    return game;
}


Menu getMenu(MenuType type) {
    Menu menu = {.numOptions=0};
    switch (type) {
    case MENU_MAIN: {
        Menu menu = {
            .options = {"New game", "Load game", "Ranking", "Exit"},
            .numOptions = 4,
            .selectedOption = 0,
            .selectionDone = false,
        };
        return menu;
    }
    case MENU_RANKING: {
        Menu menu = {
            .options = {"Back"},
            .numOptions = 1,
            .selectedOption = 0,
            .selectionDone = false,
        };
        return menu;
    }

    default:
        return menu;
        break;
    }
}

Menu updateMenu(Menu menu, Action action) {
    switch (action) {
    case ACTION_DOWN:
    case ACTION_RIGHT:
        if (menu.selectedOption < menu.numOptions - 1)
            menu.selectedOption++;
        break;
    case ACTION_UP:
    case ACTION_LEFT:
        if (menu.selectedOption > 0)
            menu.selectedOption--;
        break;
    case ACTION_YES:
        menu.selectionDone = true;
        break;
    default:
        break;
    }
    return menu;
}