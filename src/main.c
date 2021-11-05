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
int confirmationDialog(char *message, Menu *menu, GameState stateYes,
                       GameState stateNo);

int main() {
    // === Initial state variables ===
    GameState state = STATE_MENU;  // Current game state
    bool running = true;           // Indicate wether the game is running
    char username[MAX_USERNAME_LENGTH] = "";  // Player's username
    int nextState;                            // Next game state
    Game game;                                // Current game instance
    // Menus with persistent state. Start as the Main Menu
    Menu menu = getMenu(MENU_MAIN);

    // Init graphics module
    initGraphics();

    // Main game loop
    while (running && !WindowShouldClose()) {
        switch (state) {
            // Main Menu
            case STATE_MENU:
                nextState = mainMenuScreen(&menu);

                // Update the state if the next state is valid
                if (nextState != 0) state = nextState;
                break;

            // Exiting game
            case STATE_EXIT:
                running = false;
                break;

            // New game
            case STATE_NEW_GAME:
                game = newGame();
                state = STATE_PLAYING;
                break;

            // Load a game
            case STATE_LOAD_GAME:
                game = loadGame();
                state = STATE_PLAYING;
                break;

            // Playing
            case STATE_PLAYING:
                // Run the game screen
                nextState = gameScreen(&game, GetFrameTime());

                // Update the state if the next state is valid
                if (nextState != 0) state = nextState;

                if (state == STATE_WAITING_NEW_GAME ||
                    state == STATE_WAITING_EXIT_GAME) {
                    menu = getMenu(MENU_YES_NO);
                }
                break;

            // Ranking
            case STATE_RANKING:
                nextState = rankingScreen();

                // Update the state if the next state is valid
                if (nextState != 0) state = nextState;

                if (state == STATE_MENU)
                    // Reset main menu selection
                    menu.selectionDone = false;
                break;

            case STATE_GAME_OVER:
                nextState = gameOverScreen(username, &game);

                // Update the state if the next state is valid
                if (nextState != 0) state = nextState;

                if (state == STATE_MENU) menu = getMenu(MENU_MAIN);
                break;

            case STATE_WAITING_NEW_GAME:
                nextState =
                    confirmationDialog("Deseja iniciar um novo jogo?", &menu,
                                       STATE_NEW_GAME, STATE_PLAYING);

                // Update the state if the next state is valid
                if (nextState) state = nextState;

                if (state == STATE_PLAYING) {
                    game.dave.speed.x = 0;
                    game.dave.speed.y = 0;
                }
                break;

            case STATE_WAITING_EXIT_GAME:
                nextState =
                    confirmationDialog("Deseja abandonar o jogo?", &menu,
                                       STATE_MENU, STATE_PLAYING);

                // Update the state if the next state is valid
                if (nextState) state = nextState;

                if (state == STATE_MENU) menu = getMenu(MENU_MAIN);

                if (state == STATE_PLAYING) {
                    game.dave.speed.x = 0;
                    game.dave.speed.y = 0;
                }

                break;
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
 *     menu (Menu*): Pointer to the current main menu
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
    if (IsKeyPressed(KEY_ENTER)) menu = updateMenu(menu, ACTION_YES);

    // There is only one option on the menu. If the selection is done,
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

void gameOverRecord(Game *game, char* username, Menu *menu) {
    renderScoreMenu(game, username, *menu);

    int letterCount = strlen(username);
    int key = GetCharPressed();

    while (key > 0) {
        if ((key >= 32) && (key <= 126) &&
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
        *menu = updateMenu(*menu, ACTION_YES);
        RankingEntry Entry;
        Entry.score = game->score;
        strcpy(Entry.username, username);
        saveOnRanking(Entry);
        strcpy(username, "");
    }
}

void gameOver(Game *game, Menu *menu) {
    renderGameOver(game, *menu);

    if (IsKeyPressed(KEY_ENTER)) {
        *menu = updateMenu(*menu, ACTION_YES);
    }
}

int gameOverScreen(char *username, Game *game) {
    Menu menu = getMenu(MENU_OK);
    Ranking ranking = getRanking();

    if (game->score > ranking.entries[4].score) {
        gameOverRecord(game, username, &menu);
    } else {
        gameOver(game, &menu);
    }

    if (menu.selectionDone) {
        return STATE_RANKING;
    }

    return 0;
}

int confirmationDialog(char *message, Menu *menu, GameState stateYes,
                       GameState stateNo) {
    drawConfirmationDialog(message, *menu);

    // Handling of menu actions
    if (IsKeyPressed(KEY_DOWN)) *menu = updateMenu(*menu, ACTION_DOWN);
    if (IsKeyPressed(KEY_UP)) *menu = updateMenu(*menu, ACTION_UP);
    if (IsKeyPressed(KEY_ENTER)) *menu = updateMenu(*menu, ACTION_YES);

    if (menu->selectionDone) {
        if (menu->selectedOption == 0) {
            return stateYes;
        } else {
            return stateNo;
        }
    }
    return 0;
}