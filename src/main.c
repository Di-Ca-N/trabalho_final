#include <stdio.h>

#include "raylib.h"

#include "graphics.h"
#include "game.h"
#include "ranking.h"
#include "menus.h"
#include "saves.h"

typedef enum {
    STATE_MENU = 1,
    STATE_PLAYING,
    STATE_NEW_GAME,
    STATE_LOAD_GAME,
    STATE_RANKING,
    STATE_WAITING_EXIT,
} GameState;

int mainMenuScreen(Menu* menu);
int rankingScreen();
int gameScreen(Game* game);

int main() {
    // Init graphics module
    initGraphics();

    // Current game state
    GameState state = STATE_MENU;

    // Flag that indicate if the game is running
    bool running = true;

    // Init game menu 
    Menu menu = getMenu(MENU_MAIN);
    
    Game game;

    // Main game loop
    while (running) {
        switch (state) {
            case STATE_MENU: {  
                int nextState = mainMenuScreen(&menu);
                if (nextState != 0)
                    state = nextState;
                break;
            }
            case STATE_WAITING_EXIT:
                running = false;
                break;

            case STATE_LOAD_GAME: {
                game = loadGame();
                state = STATE_PLAYING;
                break;
            }

            case STATE_PLAYING: {
                int nextState = gameScreen(&game);

                if (nextState != 0) {
                    state = nextState;
                }
                break;
            }
            case STATE_RANKING: {
                int nextState = rankingScreen();
                if (nextState != 0) {
                    state = nextState;
                    menu.selectionDone = false;
                }
                break;
            }
            case STATE_NEW_GAME:
                state = STATE_PLAYING;
                game = newGame();
                menu.selectionDone = false;
                break;
        }
    }

    // Tear down graphics module
    endGraphics();

    return 0;
}

int mainMenuScreen(Menu *menu) {
    renderMainMenu(*menu);

    if(IsKeyPressed(KEY_DOWN))
        *menu = updateMenu(*menu, ACTION_DOWN);
    if(IsKeyPressed(KEY_UP))
        *menu = updateMenu(*menu, ACTION_UP);
    if(IsKeyPressed(KEY_ENTER))
        *menu = updateMenu(*menu, ACTION_YES);

    if (menu->selectionDone) {
        switch (menu->selectedOption) {
        case 0:
            return STATE_NEW_GAME;
        case 1:
            return STATE_LOAD_GAME;
        case 2:
            return STATE_RANKING;
        case 3:
            return STATE_WAITING_EXIT;
        default:
            return 0;
        }
    }
    return 0;
}

int rankingScreen() {
    Ranking ranking = getRanking();
    Menu menu = getMenu(MENU_RANKING);

    renderRanking(ranking, menu);
    if(IsKeyPressed(KEY_ENTER))
        menu = updateMenu(menu, ACTION_YES);

    if (menu.selectionDone) {
        return STATE_MENU; 
    }
    return 0;
}

int gameScreen(Game* game) {
    renderGame(*game);

    if (IsKeyDown(KEY_RIGHT)) {
        *game = handleAction(*game, ACTION_RIGHT, GetFrameTime());
    }

    if (IsKeyDown(KEY_LEFT)) {
        *game = handleAction(*game, ACTION_LEFT, GetFrameTime());
    }

    if (IsKeyReleased(KEY_LEFT)) {
        *game = handleAction(*game, ACTION_RELEASE_LEFT, GetFrameTime());
    }

    if (IsKeyReleased(KEY_RIGHT)) {
        *game = handleAction(*game, ACTION_RELEASE_RIGHT, GetFrameTime());
    }
    if (IsKeyDown(KEY_UP)) {
        *game = handleAction(*game, ACTION_UP, GetFrameTime());
    }

    if (IsKeyDown(KEY_S)) {
        saveGame(*game);
    }

    *game = updateGame(*game, GetFrameTime());
    return 0;
}