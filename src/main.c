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
#include <string.h>

#include "game.h"
#include "graphics.h"
#include "menus.h"
#include "ranking.h"
#include "raylib.h"
#include "saves.h"

// States of the game
typedef enum {
    STATE_MENU = 1,
    STATE_PLAYING,
    STATE_NEW_GAME,
    STATE_LOAD_GAME,
    STATE_RANKING,
    STATE_GAME_OVER,
    STATE_EXIT,
    STATE_WAITING_NEW_GAME,
    STATE_WAITING_EXIT_GAME,
} GameState;

// Game screens prototypes
int mainMenuScreen(Menu *menu);                  // Manage main menu screen
int rankingScreen();                             // Manage ranking screen
int gameScreen(Game *game, double lastTime);     // Manage game screen
int gameOverScreen(char *username, Game *game);  // Manage game over screen
int confirmationScreen(char* message, Menu* menu);

int main() {
    // Init graphics module
    initGraphics();

    // Current game state
    GameState state = STATE_MENU;

    // Flag that indicate if the game is running
    bool running = true;

    double lastTime;

    int nextState;
    // Init game menu
    Menu menu = getMenu(MENU_MAIN);
    Game game;
    char username[MAX_USERNAME_LENGTH] = "\0";

    // Main game loop
    while (running && !WindowShouldClose()) {
        switch (state) {
            // Main Menu state
            case STATE_MENU:
                // Run the main menu screen
                nextState = mainMenuScreen(&menu);

                // If the next state returned is valid (i.e. != 0)
                if (nextState != 0)
                    // Update state
                    state = nextState;
                break;

            // Wating exit state
            case STATE_EXIT:
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
            case STATE_LOAD_GAME:
                // Load the game save
                game = loadGame();
                // Set the state to playing
                state = STATE_PLAYING;
                lastTime = GetTime();
                break;

            // Playing game state
            case STATE_PLAYING: {
                // Run the game screen
                double nextTime = GetTime();
                nextState = gameScreen(&game, nextTime - lastTime);
                lastTime = nextTime;

                // If it returns a valid next state (i.e. != 0)
                if (nextState != 0) {
                    // Update state
                    state = nextState;

                    if (state == STATE_WAITING_NEW_GAME || state == STATE_WAITING_EXIT_GAME) {
                        menu = getMenu(MENU_YES_NO);
                    }
                }
                break;
            }

            // Ranking state
            case STATE_RANKING:
                // Run the ranking screen
                nextState = rankingScreen();
                // If the screen return a valid next state (i.e. != 0)
                if (nextState != 0) {
                    // Update the next state
                    state = nextState;
                    // Reset main menu selection
                    menu.selectionDone = false;
                }
                break;

            case STATE_GAME_OVER: 
                nextState = gameOverScreen(username, &game);
                if (nextState != 0) {
                    // Update the next state
                    state = nextState;

                    if (state == STATE_MENU) {
                        menu = getMenu(MENU_MAIN);
                    }
                }
                break;

            case STATE_WAITING_NEW_GAME: {
                int selection = confirmationScreen("Deseja iniciar um novo jogo?", &menu);
                if (selection != -1) {
                    if (selection == 0) {
                        state = STATE_NEW_GAME;
                    } else {
                        state = STATE_PLAYING;
                        lastTime = GetTime();
                        game.dave.speed.x = 0;
                        game.dave.speed.y = 0;
                    }
                }
                break;
            }

            case STATE_WAITING_EXIT_GAME: {
                int selection = confirmationScreen("Deseja abandonar o jogo?", &menu);
                if (selection != -1) {
                    if (selection == 0) {
                        state = STATE_MENU;
                        menu = getMenu(MENU_MAIN);
                    } else {
                        state = STATE_PLAYING;
                        lastTime = GetTime();
                        game.dave.speed.x = 0;
                        game.dave.speed.y = 0;
                    }
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
    if (IsKeyPressed(KEY_DOWN)) *menu = updateMenu(*menu, ACTION_DOWN);
    if (IsKeyPressed(KEY_UP)) *menu = updateMenu(*menu, ACTION_UP);
    if (IsKeyPressed(KEY_ENTER)) *menu = updateMenu(*menu, ACTION_YES);

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
                return STATE_EXIT;
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
    Menu menu = getMenu(MENU_OK);

    // Draw ranking on the screen
    renderRanking(ranking, menu);

    // Handling menu action
    if (IsKeyPressed(KEY_ENTER)) {
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
int gameScreen(Game *game, double timeDelta) {
    // Draw game on the screen
    renderGame(game);

    // Handling game actions

    // Movement actions
    if (IsKeyDown(KEY_RIGHT)) handleAction(game, ACTION_RIGHT);
    if (IsKeyDown(KEY_LEFT)) handleAction(game, ACTION_LEFT);
    if (IsKeyReleased(KEY_LEFT)) handleAction(game, ACTION_RELEASE_LEFT);
    if (IsKeyReleased(KEY_RIGHT)) handleAction(game, ACTION_RELEASE_RIGHT);
    if (IsKeyDown(KEY_UP)) handleAction(game, ACTION_UP);
    if (IsKeyDown(KEY_DOWN)) handleAction(game, ACTION_DOWN);
    if (IsKeyPressed(KEY_SPACE)) handleAction(game, ACTION_SPACE);
    if (IsKeyReleased(KEY_DOWN)) handleAction(game, ACTION_RELEASE_DOWN);
    if (IsKeyReleased(KEY_UP)) handleAction(game, ACTION_RELEASE_UP);

    // Special actions
    if (IsKeyPressed(KEY_S)) saveGame(*game);
    if (IsKeyPressed(KEY_N)) return STATE_WAITING_NEW_GAME;
    if (IsKeyPressed(KEY_ESCAPE)) return STATE_WAITING_EXIT_GAME;

    // Update the game based on the actions taken by the user
    updateGame(game, timeDelta);

    // Game events
    if (game->gameOver) return STATE_GAME_OVER;
    if (game->nextStage) loadNextStage(game);

    return 0;
}

int gameOverScreen(char *username, Game *game) {
    Menu menu = getMenu(MENU_OK);
    Ranking ranking = getRanking();

    if (game->score > ranking.entries[4].score) {
        renderScoreMenu(game, username, menu);

        int letterCount = strlen(username);

        int key = GetCharPressed();

        while (key > 0) {
            if ((key >= 32) && (key <= 125) &&
                (letterCount < MAX_USERNAME_LENGTH)) {
                username[letterCount] = (char)key;
                username[letterCount + 1] = '\0';
                letterCount++;
            }

            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE)) {
            letterCount--;
            if (letterCount < 0) letterCount = 0;
            username[letterCount] = '\0';
        }

        if (IsKeyPressed(KEY_ENTER) && letterCount) {
            menu = updateMenu(menu, ACTION_YES);
            RankingEntry Entry;
            Entry.score = game->score;
            strcpy(Entry.username, username);
            saveOnRanking(Entry);
            strcpy(username, "\0");
        }
    } else {
        renderGameOver(game, menu);
  
        if (IsKeyPressed(KEY_ENTER)) {
            menu = updateMenu(menu, ACTION_YES);
        }
    }

    if (menu.selectionDone) {
        return STATE_RANKING;
    }

    return 0;
}

int confirmationScreen(char* message, Menu* menu) {
    drawConfirmationDialog(message, *menu);

    // Handling of menu actions
    if (IsKeyPressed(KEY_DOWN)) *menu = updateMenu(*menu, ACTION_DOWN);
    if (IsKeyPressed(KEY_UP)) *menu = updateMenu(*menu, ACTION_UP);
    if (IsKeyPressed(KEY_ENTER)) *menu = updateMenu(*menu, ACTION_YES);

    if (menu->selectionDone) {
        return menu->selectedOption;
    }
    return -1;
}