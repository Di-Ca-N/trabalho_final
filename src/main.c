#include "raylib.h"

#include <stdio.h>

#include "graphics.h"

typedef enum {
    STATE_MENU = 1,
    STATE_PLAYING,
    STATE_NEW_GAME,
    STATE_LOAD_GAME,
    STATE_RANKING,
    STATE_WAITING_EXIT,
} GameState;

int mainMenuScreen(Menu *menu);

int main() {
    // Init graphics module
    initGraphics();

    // Init game menu 
    Menu menu = getMenu(MENU_MAIN);

    // Current game state
    GameState state = STATE_MENU;

    // Flag that indicate if the game is running
    bool running = true;

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
            printf("Jogar\n");
            state = STATE_MENU;
            menu.selectionDone = false;
            break;
        case STATE_RANKING:
            printf("Ranking\n");
            state = STATE_MENU;
            menu.selectionDone = false;
            break;
        case STATE_NEW_GAME:
            printf("New Game\n");
            state = STATE_MENU;
            menu.selectionDone = false;
            break;
        }
    }

    endGraphics();

    return 0;
}

int mainMenuScreen(Menu *menu) {
    renderMenu(*menu);

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