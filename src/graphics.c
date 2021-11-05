#include "graphics.h"

#include <stdio.h>   // snprintf
#include <string.h>  // strlen

#include "raylib.h"

void initGraphics() {
    // Init game window
    InitWindow(TILE_SIZE * NUM_TILES_WIDTH, TILE_SIZE * NUM_TILES_HEIGHT,
               "Dangerous Dave");

    // Set game to run at 60 fps
    SetTargetFPS(60);

    // Remove default exit key
    SetExitKey(0);
}

// Draw a menu to the screen, starting at xPos and yPos
void drawMenu(Menu menu, int xPos, int yPos) {
    // Loop to draw menu options
    for (int i = 0; i < menu.numOptions; i++) {
        // Buffer to hold option text. Settled to MAX_OPTION_LENGTH + 2 
        // to account for extra characters added to the buffer on the 
        // "if" below
        char optionBuffer[MAX_OPTION_LENGTH + 2];

        // If the option being current redendered is the selected option
        if (menu.selectedOption == i) {
            // Add a marker to the option
            snprintf(optionBuffer, MAX_OPTION_LENGTH + 2, "> %s",
                     menu.options[i]);
        } else {
            // Otherwise, add no mark
            snprintf(optionBuffer, MAX_OPTION_LENGTH + 2, "  %s",
                     menu.options[i]);
        }
        // Draw option text to screen
        int itemYPos = yPos + 2 + i * TEXT_FONT_SIZE;
        DrawText(optionBuffer, xPos, itemYPos, TEXT_FONT_SIZE, BLACK);
    }
}

// Render the main menu scren
void renderMainMenu(Menu menu) {
    SetWindowSize(TILE_SIZE * NUM_TILES_WIDTH, TILE_SIZE * NUM_TILES_HEIGHT);
    // Start drawing
    BeginDrawing();

    // Clear background
    ClearBackground(RAYWHITE);

    // Draw menu title
    DrawText("Dangerous Dave", TILE_SIZE * 3, TILE_SIZE * 3, HEADER_FONT_SIZE,
             BLACK);

    // Draw menu options
    drawMenu(menu, TILE_SIZE * 3, TILE_SIZE * 3 + HEADER_FONT_SIZE + 10);

    // End drawing
    EndDrawing();
}

// Render the ranking screen
void renderRanking(Ranking ranking, Menu menu) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText("Ranking", TILE_SIZE * 3, TILE_SIZE * 3, HEADER_FONT_SIZE, BLACK);

    char rankingEntryBuffer[MAX_USERNAME_LENGTH + 12];

    for (int i = 0; i < 5; i++) {
        if (strlen(ranking.entries[i].username) == 0) {
            snprintf(rankingEntryBuffer, MAX_USERNAME_LENGTH + 12,
                     "%d. %10s", i + 1, "---");
        } else {
            snprintf(rankingEntryBuffer, MAX_USERNAME_LENGTH + 12,
                     "%d. %10s    %04d", i + 1, ranking.entries[i].username,
                     ranking.entries[i].score);
        }

        DrawText(rankingEntryBuffer, TILE_SIZE * 3,
                 TILE_SIZE * 3 + HEADER_FONT_SIZE + 12 + i * TEXT_FONT_SIZE,
                 TEXT_FONT_SIZE, BLACK);
    }
    int menuYPos = TILE_SIZE * 3 + HEADER_FONT_SIZE + 10 + 5 * TEXT_FONT_SIZE;
    drawMenu(menu, TILE_SIZE * 3, menuYPos);
    EndDrawing();
}

// Render game icons from map
void renderGame(Game* game) {
    SetWindowSize(game->map.width * TILE_SIZE,
                  (game->map.height + 2) * TILE_SIZE);
    BeginDrawing();
    ClearBackground(RAYWHITE);
    // Show current score on screen at top left corner

    char pontuacao[20] = "PONTUAÇÃO:";
    snprintf(pontuacao, 20, "PONTUAÇÃO: %d", game->score);
    DrawText(pontuacao, TILE_SIZE * 0.5, TILE_SIZE * 0.8, TEXT_MAP_SIZE, BLACK);

    char vidas[10] = "VIDAS:";
    snprintf(vidas, 10, "VIDAS: %d", game->dave.lives);

    // Show remaining lives on screen
    DrawText(vidas, TILE_SIZE * 15.0, TILE_SIZE * 0.8, TEXT_MAP_SIZE, MAROON);

    // Show current level on screen
    char nivel[15] = "NÍVEL:";
    snprintf(nivel, 15, "NÍVEL: %d", game->level);
    DrawText(nivel, TILE_SIZE * 25.0, TILE_SIZE * 0.8, TEXT_MAP_SIZE, BLACK);

    // Show message on screen if Dave collects the trophy
    if (game->dave.gotTrophy) {
        DrawText("TROFEU CONQUISTADO", TILE_SIZE * 35.0, TILE_SIZE * 0.8,
                 TEXT_MAP_SIZE, BLACK);
    }
    // Show message on screen if Dave acquires the jetpack
    if (game->dave.hasJetpack) {
        DrawText("JETPACK ADQUIRIDO", TILE_SIZE * 52.0, TILE_SIZE * 0.8,
                 TEXT_MAP_SIZE, BLACK);
    }
    // Show message on screen if jetpack is active
    if (game->dave.flying) {
        DrawText("JETPACK ATIVADO", TILE_SIZE * 67.0, TILE_SIZE * 0.8,
                 TEXT_MAP_SIZE, BLACK);
    }

    for (int row = 2; (row - 2) < game->map.height; row++) {
        for (int col = 0; col < game->map.width; col++) {
            switch (game->map.stage[row - 2][col]) {
                case WALL:
                    // Render walls
                    DrawRectangle(col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE,
                                  TILE_SIZE, GREEN);
                    break;
                case CROWN:
                    // Render crown
                    DrawCircle(col * TILE_SIZE + (TILE_SIZE / 2),
                               row * TILE_SIZE + (TILE_SIZE / 2),
                               (TILE_SIZE / 2), YELLOW);
                    break;
                case RUBY: {
                    // Render ruby

                    Vector2 v1 = {col * TILE_SIZE, row * TILE_SIZE};
                    Vector2 v2 = {(col - 0.4) * TILE_SIZE,
                                  (row + 1) * TILE_SIZE};
                    Vector2 v3 = {(col + 0.4) * TILE_SIZE,
                                  (row + 1) * TILE_SIZE};

                    DrawTriangle(v1, v2, v3, DARKGREEN);
                    break;
                }
                case AMETHYST:
                    // Render amethyst gem
                    DrawEllipse((col + .5) * TILE_SIZE, (row + .5) * TILE_SIZE,
                                (TILE_SIZE / 2), (TILE_SIZE / 3), PURPLE);
                    break;
                case SAPHIRE: {
                    // Render saphire gem

                    Vector2 v4 = {(col + 0.25) * TILE_SIZE, row * TILE_SIZE};
                    Vector2 v5 = {col * TILE_SIZE, (row + 1) * TILE_SIZE};
                    Vector2 v6 = {(col + 0.5) * TILE_SIZE,
                                  (row + 1) * TILE_SIZE};

                    DrawTriangle(v4, v5, v6, DARKBLUE);
                    break;
                }
                case RING:
                    // Render ring
                    DrawCircle(col * TILE_SIZE + (TILE_SIZE / 2.5),
                               row * TILE_SIZE + (TILE_SIZE / 3),
                               (TILE_SIZE / 2.5), GRAY);
                    break;
                case DOOR:
                    // Render door
                    DrawRectangle(col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE,
                                  TILE_SIZE, BROWN);
                    break;
                case WATER:
                    // Render water
                    DrawRectangle(col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE,
                                  TILE_SIZE, SKYBLUE);
                    break;
                case FIRE:
                    // Render fire
                    DrawRectangle(col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE,
                                  TILE_SIZE, RED);

                    break;
                case JETPACK:
                    // Render jetpack
                    DrawRectangle(col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE,
                                  TILE_SIZE, ORANGE);
                    break;
                case TROPHY: {
                    // Render trophy

                    Vector2 v7 = {(col + 0.5) * TILE_SIZE, (row)*TILE_SIZE};
                    Vector2 v8 = {col * TILE_SIZE, (row + 1) * TILE_SIZE};
                    Vector2 v9 = {(col + 1.0) * TILE_SIZE,
                                  (row + 1) * TILE_SIZE};
                    DrawTriangle(v7, v8, v9, GOLD);
                }
            }
        }
    }

    DrawRectangle(game->dave.position.x * TILE_SIZE,
                  (game->dave.position.y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE,
                  BLUE);
    EndDrawing();
}


void renderGameOver(Game* game, Menu menu) {
    SetWindowSize(TILE_SIZE * NUM_TILES_WIDTH, TILE_SIZE * NUM_TILES_HEIGHT);

    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText("Fim de Jogo", TILE_SIZE * 7, TILE_SIZE * 5,
             HEADER_FONT_SIZE, BLACK);

    char pontuacao[40] = "";
    snprintf(pontuacao, 40, "Sua pontuação: %d", game->score);
    DrawText(pontuacao, TILE_SIZE * 7, TILE_SIZE * 7, TEXT_FONT_SIZE, BLACK);

    drawMenu(menu, TILE_SIZE * 7, TILE_SIZE * 10);
    EndDrawing();
}

void renderScoreMenu(Game *game ,char *username , Menu menu) {

    SetWindowSize(TILE_SIZE * NUM_TILES_WIDTH, TILE_SIZE * NUM_TILES_HEIGHT);

    BeginDrawing();
    ClearBackground(RAYWHITE);

   DrawText("Fim de Jogo", TILE_SIZE * 3, TILE_SIZE * 3,
             HEADER_FONT_SIZE, BLACK);

    char pontuacao[40] = "";
    snprintf(pontuacao, 40, "Sua pontuação: %d", game->score);
    DrawText(pontuacao, TILE_SIZE * 3, TILE_SIZE * 5, TEXT_FONT_SIZE, BLACK);


    DrawText("Parabéns! Sua pontuação está entre as 5 maiores.", TILE_SIZE * 3, TILE_SIZE * 8.5,
      19, BLACK); 
    DrawText("Digite seu username:", TILE_SIZE * 3, TILE_SIZE * 9.5,
     TEXT_FONT_SIZE , BLACK); 
    
    DrawRectangleLines(TILE_SIZE * 3 , TILE_SIZE * 11, 360 , 30 , BLACK ); 
    DrawText(username , (TILE_SIZE * 3) + 8 , (TILE_SIZE * 11) + 8, TEXT_FONT_SIZE, BLACK);

    drawMenu(menu, TILE_SIZE * 3, TILE_SIZE * 13.5);
    EndDrawing();
    
}

void drawConfirmationDialog(char* message, Menu menu) {
    int height = GetScreenHeight();
    int width = GetScreenWidth();
    int centerHeight = height / 2;
    int centerWidth = width / 2;

    Rectangle dialogBox = {centerWidth - 175, centerHeight - 75, 350, 150};

    BeginDrawing();
    DrawRectangle(dialogBox.x, dialogBox.y, dialogBox.width, dialogBox.height, LIGHTGRAY);
    DrawText(message, dialogBox.x + 15, dialogBox.y + 30, TEXT_FONT_SIZE, BLACK);
    drawMenu(menu, dialogBox.x + 15, dialogBox.y + 30 + HEADER_FONT_SIZE);
    EndDrawing();
}

void endGraphics() { CloseWindow(); }
