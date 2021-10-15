#include <stdio.h>

#include "raylib.h"

#include "graphics.h"
#include "game.h"
#include "ranking.h"
#include "menus.h"

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

int main() {
    Map map;
    map = loadMap("assets/stages/fase_01.txt");
    printf("Altura do mapa %d\n", map.height);
    printf("Começo do dave: %d %d\n", map.daveStart[0], map.daveStart[1]);

    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 97; j++) {
            printf("%c", map.stage[i][j]);
        }
        printf("\n");
    }
    
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
        case STATE_LOAD_GAME:
            printf("Carregar jogo\n");
            state = STATE_MENU;
            menu.selectionDone = false;
            break;
        case STATE_PLAYING:
            renderGame(game);

            if (IsKeyDown(KEY_RIGHT)) {
                game = handleAction(game, ACTION_RIGHT, GetFrameTime());
            }

            if (IsKeyDown(KEY_LEFT)) {
                game = handleAction(game, ACTION_LEFT, GetFrameTime());
            }

            if (IsKeyReleased(KEY_LEFT)) {
                game = handleAction(game, ACTION_RELEASE_LEFT, GetFrameTime());
            }

            if (IsKeyReleased(KEY_RIGHT)) {
                game = handleAction(game, ACTION_RELEASE_RIGHT, GetFrameTime());
            }
            if (IsKeyDown(KEY_UP)) {
                game = handleAction(game, ACTION_UP, GetFrameTime());
            }
            game = updateGame(game, GetFrameTime());
            break;

        case STATE_RANKING: {
            int nextState = rankingScreen();
            if (nextState != 0) {
                state = nextState;
                menu.selectionDone = false;
            }
            break;
        }
        case STATE_NEW_GAME:
            printf("New Game\n");
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
