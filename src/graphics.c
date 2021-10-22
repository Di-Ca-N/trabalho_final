#include "graphics.h"

#include <stdio.h>  // snprintf
#include <string.h> // strlen
#include "raylib.h"

void initGraphics()
{
    // Init game window
    InitWindow(
        TILE_SIZE * NUM_TILES_WIDTH,
        TILE_SIZE * NUM_TILES_HEIGHT,
        "Dangerous Dave");

    // Set game to run at 60 fps
    SetTargetFPS(60);

    // Remove default exit key
    SetExitKey(0);
}

// Draw a menu to the screen, starting at xPos and yPos
void drawMenu(Menu menu, int xPos, int yPos)
{
    // Loop to draw menu options
    for (int i = 0; i < menu.numOptions; i++)
    {
        // Buffer to hold option text. Set to MAX_OPTION_LENGTH + 2 to
        // account for extra characters added to the buffer on the "if" below
        char optionBuffer[MAX_OPTION_LENGTH + 2];

        // If the option being current redendered is the selected option
        if (menu.selectedOption == i)
        {
            // Add a marker to the option
            snprintf(optionBuffer, MAX_OPTION_LENGTH + 2,
                     "> %s", menu.options[i]);
        }
        else
        {
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
void renderMainMenu(Menu menu)
{
    // Start drawing
    BeginDrawing();

    // Clear background
    ClearBackground(RAYWHITE);

    // Draw menu title
    DrawText("Dangerous Dave", TILE_SIZE * 3, TILE_SIZE * 3,
             HEADER_FONT_SIZE, BLACK);

    // Draw menu options
    drawMenu(menu, TILE_SIZE * 3, TILE_SIZE * 3 + HEADER_FONT_SIZE + 10);

    // End drawing
    EndDrawing();
}

// Render the ranking screen
void renderRanking(Ranking ranking, Menu menu)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText("Ranking", TILE_SIZE * 3, TILE_SIZE * 3, HEADER_FONT_SIZE, BLACK);

    char rankingEntryBuffer[MAX_USERNAME_LENGTH + 12];

    for (int i = 0; i < 5; i++)
    {
        if (strlen(ranking.entries[i].username) == 0)
        {
            snprintf(
                rankingEntryBuffer,
                MAX_USERNAME_LENGTH + 12,
                "%d. %10s    %04d",
                i + 1,
                "---",
                ranking.entries[i].score);
        }
        else
        {
            snprintf(
                rankingEntryBuffer,
                MAX_USERNAME_LENGTH + 12,
                "%d. %10s    %04d", i + 1,
                ranking.entries[i].username,
                ranking.entries[i].score);
        }

        DrawText(
            rankingEntryBuffer,
            TILE_SIZE * 3,
            TILE_SIZE * 3 + HEADER_FONT_SIZE + 12 + i * TEXT_FONT_SIZE,
            TEXT_FONT_SIZE,
            BLACK);
    }
    int menuYPos = TILE_SIZE * 3 + HEADER_FONT_SIZE + 10 + 5 * TEXT_FONT_SIZE;
    drawMenu(menu, TILE_SIZE * 3, menuYPos);
    EndDrawing();
}

void renderGame(Game *game)
{ // Render game icons from map
    SetWindowSize(game->map.width * TILE_SIZE, (game->map.height + 2) * TILE_SIZE);
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText(
        "PONTUAÇÃO: 1000",
        TILE_SIZE * 0.5,
        TILE_SIZE * 0.8,
        TEXT_MAP_SIZE,
        BLACK);

    DrawText(
        "3 VIDAS",
        TILE_SIZE * 15.0,
        TILE_SIZE * 0.8,
        TEXT_MAP_SIZE,
        MAROON);

    DrawText(
        "NIVEL: 1",
        TILE_SIZE * 25.0,
        TILE_SIZE * 0.8,
        TEXT_MAP_SIZE,
        BLACK);

    if (game->dave.hasJetpack)
    {
        DrawText(
            "JETPACK ATIVADO",
            TILE_SIZE * 35.0,
            TILE_SIZE * 0.8,
            TEXT_MAP_SIZE,
            BLACK);
    }

     if (game->dave.gotTrophy)  
     {
         DrawText(
            "TROFEU CONQUISTADO",
            TILE_SIZE * 52.0,
            TILE_SIZE * 0.8,
            TEXT_MAP_SIZE,
            BLACK);
     }
       

    for (int row = 2; (row - 2) < game->map.height; row++)
    {
        for (int col = 0; col < game->map.width; col++)
        {
            switch (game->map.stage[row - 2][col])
            {
            case WALL: // Render walls
                DrawRectangle(col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE, GREEN);
                break;
            case CROWN: // Render crown
                DrawCircle(col * TILE_SIZE + (TILE_SIZE / 2), row * TILE_SIZE + (TILE_SIZE / 2), (TILE_SIZE / 2), YELLOW);
                break;
            case RUBY:
            { //Render ruby gem

                Vector2 v1 = {col * TILE_SIZE, row * TILE_SIZE};
                Vector2 v2 = {(col - 0.4) * TILE_SIZE, (row + 1) * TILE_SIZE};
                Vector2 v3 = {(col + 0.4) * TILE_SIZE, (row + 1) * TILE_SIZE};

                DrawTriangle(v1, v2, v3, DARKGREEN);
                break;
            }
            case AMETIST: //Render ametist gem
                DrawEllipse(col * TILE_SIZE, row * TILE_SIZE, (TILE_SIZE / 2), (TILE_SIZE / 3), PURPLE);
                break;
            case SAPHIRE:
            { //Render saphire gem

                Vector2 v4 = {(col + 0.25) * TILE_SIZE, row * TILE_SIZE};
                Vector2 v5 = {col * TILE_SIZE, (row + 1) * TILE_SIZE};
                Vector2 v6 = {(col + 0.5) * TILE_SIZE, (row + 1) * TILE_SIZE};

                DrawTriangle(v4, v5, v6, DARKBLUE);
                break;
            }
            case RING: // Render ring
                DrawCircle(col * TILE_SIZE + (TILE_SIZE / 2.5), row * TILE_SIZE + (TILE_SIZE / 3), (TILE_SIZE / 2.5), GRAY);
                break;
            case DOOR: // Render door
                DrawRectangle(col * TILE_SIZE, (row * TILE_SIZE - 25), TILE_SIZE, (TILE_SIZE + 25), BROWN);
                break;
            case WATER: // Render water
                DrawRectangle(col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE, SKYBLUE);
                break;
            case FIRE: // Render fire
                DrawRectangle(col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE, RED);

                break;
            case JETPACK: // Render jetpack
                DrawRectangle(col * TILE_SIZE, (row * TILE_SIZE - 8), TILE_SIZE, (TILE_SIZE + 8), ORANGE);
                break;
            case TROPHY:
            { // Render trophy

                Vector2 v7 = {(col + 0.5) * TILE_SIZE, (row)*TILE_SIZE};
                Vector2 v8 = {col * TILE_SIZE, (row + 1) * TILE_SIZE};
                Vector2 v9 = {(col + 1.0) * TILE_SIZE, (row + 1) * TILE_SIZE};
                DrawTriangle(v7, v8, v9, GOLD);
            }
            }
        }
    }

    DrawRectangle(game->dave.position.x * TILE_SIZE, (game->dave.position.y + 2) * TILE_SIZE, TILE_SIZE, TILE_SIZE, BLUE);
    DrawFPS(10, 10);
    EndDrawing();
}

void endGraphics()
{
    CloseWindow();
}
