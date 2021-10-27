/**
 * ==== Dangerous Dave ====
 * 
 * Esse trabalho se trata de um jogo inspirado no jogo Dangerous Dave, 
 * de 1988
 * 
 * Jogo desenvolvido como trabalho final da disciplina 
 * INF-01202 - Algoritmos e Programação
 * 
 * Professor: Lucas Rafael Costella Pessuto
 * Estudantes: Diego Cardoso Nunes, Enzo Sergi Berquo Xavier
*/

#include <stdio.h>

#include "raylib.h"

#include "graphics.h"
#include "game.h"
#include "ranking.h"
#include "menus.h"
#include "saves.h"

// States of the game
typedef enum {
    STATE_MENU = 1,
    STATE_PLAYING,
    STATE_NEW_GAME,
    STATE_LOAD_GAME,
    STATE_RANKING,
    STATE_WAITING_EXIT,
} GameState;

// Game screens prototypes
int mainMenuScreen(Menu* menu); // Manage main menu screen
int rankingScreen();            // Manage ranking screen
int gameScreen(Game* game, double lastTime);     // Manage game screen

int main() {
    // Init graphics module
    initGraphics();

    // Current game state
    GameState state = STATE_MENU;

    // Flag that indicate if the game is running
    bool running = true;

    double lastTime;
    // Init game menu 
    Menu menu = getMenu(MENU_MAIN);
    
    Game game;

    // Main game loop
    while (running && !WindowShouldClose()) {
        switch (state) {
            // Main Menu state
            case STATE_MENU: {
                // Run the main menu screen  
                int nextState = mainMenuScreen(&menu);

                // If the next state returned is valid (i.e. != 0)
                if (nextState != 0)
                    // Update state
                    state = nextState;
                break;
            }

            // Wating exit state
            case STATE_WAITING_EXIT:
                // ToDo: Ask for confirmation before exit
                running = false;
                break;
            // New game state
            case STATE_NEW_GAME:
                // Create a new game
                game = newGame();
                // Set the state to playing
                state = STATE_PLAYING;
                lastTime = GetTime();
                break;

            // Load game state
            case STATE_LOAD_GAME: {
                // Load the game save
                game = loadGame();
                // Set the state to playing
                state = STATE_PLAYING;
                lastTime = GetTime();
                break;
            }

            // Playing game state
            case STATE_PLAYING: {
                // Run the game screen
                double nextTime = GetTime();
                int nextState = gameScreen(&game, nextTime - lastTime);
                lastTime = nextTime;

                // If it returns a valid next state (i.e. != 0)
                if (nextState != 0) {
                    // Update state
                    state = nextState;
                }
                break;
            }
            
            // Ranking state
            case STATE_RANKING: {
                // Run the ranking screen
                int nextState = rankingScreen();
                // If the screen return a valid next state (i.e. != 0)
                if (nextState != 0) {
                    // Update the next state
                    state = nextState;
                    // Reset main menu selection
                    menu.selectionDone = false;
                }
                break;
            }
        }
    }

    // Tear down graphics module
    endGraphics();

    return 0;
}

/**
 * Manage the main menu screen.
 * 
 * Arguments:
 *     menu (Menu*): Pointer to the current main menu, to be managed
*/
int mainMenuScreen(Menu *menu) {
    // Draw menu on the screen
    renderMainMenu(*menu);

    // Handling of menu actions
    if(IsKeyPressed(KEY_DOWN))
        *menu = updateMenu(*menu, ACTION_DOWN);
    if(IsKeyPressed(KEY_UP))
        *menu = updateMenu(*menu, ACTION_UP);
    if(IsKeyPressed(KEY_ENTER))
        *menu = updateMenu(*menu, ACTION_YES);

    // Process option if it was selected
    if (menu->selectionDone) {
        // Each selected option correspond to a new state
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
                // Every other return code should not occur. Returns 0
                // to keep the current state
                return 0;
        }
    }
    return 0;
}

/**
 * Manage the ranking screen.
*/
int rankingScreen() {
    // Get the current ranking
    Ranking ranking = getRanking();
    // Get the ranking menu. The menu contains only one option, so it
    // can be reloaded every update
    Menu menu = getMenu(MENU_RANKING);

    // Draw ranking on the screen
    renderRanking(ranking, menu);

    // Handling menu action
    if(IsKeyPressed(KEY_ENTER)) {
        menu = updateMenu(menu, ACTION_YES);
    }

    // As there is only one option on the menu. If the selection is done,
    // return the next state
    if (menu.selectionDone) {
        return STATE_MENU; 
    }

    // If no option was selected, return 0 (keep the same state)
    return 0;
}

/**
 * Manage the game screen
 * 
 * Arguments:
 *     game (Game*): Pointer to the current game to be managed
 *     timeDelta (double): Time elapsed since last update
*/
int gameScreen(Game* game, double timeDelta) {
    // Draw game on the screen
    renderGame(game);

    // Handling game actions

    // Movement actions
    if (IsKeyDown(KEY_RIGHT)) {
        handleAction(game, ACTION_RIGHT);
    }

    if (IsKeyDown(KEY_LEFT)) {
        handleAction(game, ACTION_LEFT);
    }

    if (IsKeyReleased(KEY_LEFT)) {
        handleAction(game, ACTION_RELEASE_LEFT);
    }

    if (IsKeyReleased(KEY_RIGHT)) {
        handleAction(game, ACTION_RELEASE_RIGHT);
    }

    if (IsKeyDown(KEY_UP)) {
        handleAction(game, ACTION_UP);
    }

    if (IsKeyDown(KEY_DOWN)) {
        handleAction(game, ACTION_DOWN);
    }
    
    if (IsKeyPressed(KEY_SPACE)) {
        handleAction(game, ACTION_SPACE);
    }
    
    if (IsKeyReleased(KEY_DOWN)) {
        handleAction(game, ACTION_RELEASE_DOWN);
    }
    
    if (IsKeyReleased(KEY_UP)) {
        handleAction(game, ACTION_RELEASE_UP);
    }

    // Save action
    if (IsKeyDown(KEY_S)) {
        saveGame(*game);
    }

    // Update the game based on the actions taken by the user
    updateGame(game, timeDelta);

    return 0;
}