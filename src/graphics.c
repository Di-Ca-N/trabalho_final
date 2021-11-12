#include "graphics.h"

#include <stdio.h>
#include <string.h>

#include "raylib.h"
#include "raymath.h"

static Camera2D getCamera(Game *game);
static void drawMenu(Menu menu, int xPos, int yPos);

/**
 * Initialize the graphics module
 * 
 * Arguments:
 *    spriteSheet (SpriteSheet*): Pointer to the sprite sheet where the
 *       game sprites should be loaded
 */
void initGraphics(SpriteSheet* spriteSheet) {
    // Init game window
    InitWindow(TILE_SIZE * NUM_TILES_WIDTH, 
               TILE_SIZE * NUM_TILES_HEIGHT,
               "Dangerous Dave");

    // Loading sprites into the sprite sheet
    spriteSheet->wall = LoadTexture("assets/sprites/wall.png");
    spriteSheet->dave = LoadTexture("assets/sprites/dave.png");
    spriteSheet->daveFlying = LoadTexture("assets/sprites/dave_flying.png");
    spriteSheet->crown = LoadTexture("assets/sprites/crown.png");
    spriteSheet->gem = LoadTexture("assets/sprites/gem.png");
    spriteSheet->gem2 = LoadTexture("assets/sprites/gem2.png");
    spriteSheet->ring = LoadTexture("assets/sprites/ring.png");
    spriteSheet->trophy = LoadTexture("assets/sprites/trophy.png");
    spriteSheet->door = LoadTexture("assets/sprites/door.png");
    spriteSheet->doorClosed = LoadTexture("assets/sprites/door_closed.png");
    spriteSheet->water = LoadTexture("assets/sprites/water.png");
    spriteSheet->fire = LoadTexture("assets/sprites/fire.png");
    spriteSheet->jetpack = LoadTexture("assets/sprites/hat.png");

    // Set game to run at 60 fps
    SetTargetFPS(60);

    // Remove default exit key
    SetExitKey(0);
}

/**
 * Draw the main menu screen
 * 
 * Arguments:
 *     menu (Menu): Menu to be drawn
 */
void renderMainMenu(Menu menu) {
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

/**
 * Draw a menu to the screen, one option per line.
 * 
 * Arguments:
 *     menu (Menu): Menu to be drawn
 *     xPos (int): X position of the menu first option
 *     yPos (int): Y position of the menu first option 
 */
static void drawMenu(Menu menu, int xPos, int yPos) {
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

/**
 * Draw the ranking screen
 * 
 * Arguments:
 *     ranking (Ranking): Ranking to be drawn
 *     menu (Menu): Menu of the screen
 */
void renderRanking(Ranking ranking, Menu menu) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText("Ranking", TILE_SIZE * 3, TILE_SIZE * 3, HEADER_FONT_SIZE, BLACK);

    for (int i = 0; i < RANKING_ENTRIES; i++) {
        int yPos = TILE_SIZE * 3 + HEADER_FONT_SIZE + 6 + i * TEXT_FONT_SIZE;
        char pos[3];
        snprintf(pos, sizeof(pos), "%d.", i + 1);

        DrawText(pos, TILE_SIZE * 3, yPos, TEXT_FONT_SIZE, BLACK);

        if (strlen(ranking.entries[i].username) == 0) {
            DrawText("---", TILE_SIZE * 3, yPos, TEXT_FONT_SIZE, BLACK);
        } else {
            char username[MAX_USERNAME_LENGTH + 5];
            snprintf(username, sizeof(username), "%-15s", ranking.entries[i].username);
            DrawText(username, TILE_SIZE * 5, yPos, TEXT_FONT_SIZE, BLACK);

            char score[6];
            snprintf(score, sizeof(score), "%5d", ranking.entries[i].score);
            DrawText(score, TILE_SIZE * 20, yPos, TEXT_FONT_SIZE, BLACK);
        }
    }

    int menuYPos = TILE_SIZE * 3 + HEADER_FONT_SIZE + 10 + RANKING_ENTRIES * TEXT_FONT_SIZE;

    drawMenu(menu, TILE_SIZE * 3, menuYPos);
    EndDrawing();
}

/**
 * Draw game
 * 
 * Arguments:
 *     game (Game*): Pointer to the game to be drawn
 *     spriteSheet (SpriteSheet*): Pointer to the sprite sheet with the 
 *         textures of the game elements
 */
void renderGame(Game *game, SpriteSheet *spriteSheet) {
    // Get the current game camera
    Camera2D camera = getCamera(game);

    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Start 2D camera context
    BeginMode2D(camera);

    // Loop to draw current stage
    for (int row = 0; row < game->map.height; row++) {
        for (int col = 0; col < game->map.width; col++) {
            // X and Y screen positions of the current tile
            int xPos = col * TILE_SIZE;
            int yPos = row * TILE_SIZE;
            
            // Drawing background tile
            DrawTexture(spriteSheet->wall, xPos, yPos, DARKBROWN);

            // Drawing game objects
            switch (game->map.stage[row][col]) {
                case WALL:
                    DrawTexture(spriteSheet->wall, xPos, yPos, WHITE);
                    break;
                case CROWN:
                    DrawTexture(spriteSheet->crown, xPos, yPos, WHITE);
                    break;
                case RUBY:
                    DrawTexture(spriteSheet->gem, xPos, yPos, RED);
                    break;
                case AMETHYST:
                    DrawTexture(spriteSheet->gem, xPos, yPos, PURPLE);
                    break;
                case SAPHIRE:
                    DrawTexture(spriteSheet->gem2, xPos, yPos, DARKBLUE);
                    break;
                case RING:
                    DrawTexture(spriteSheet->ring, xPos, yPos, WHITE);
                    break;
                case DOOR:
                    DrawTexture(spriteSheet->door, xPos, yPos, WHITE);
                    break;
                case WATER:
                    DrawTexture(spriteSheet->water, xPos, yPos, WHITE);
                    break;
                case FIRE:
                    DrawTexture(spriteSheet->fire, xPos, yPos, WHITE);
                    break;
                case JETPACK:
                    DrawTexture(spriteSheet->jetpack, xPos, yPos, WHITE);
                    break;
                case TROPHY:
                    DrawTexture(spriteSheet->trophy, xPos, yPos, GOLD);
                    break;
            }
        }
    }

    // Dave Sprite selection
    Texture2D daveSprite;
    Rectangle spriteRect;
    
    // Dave have different sprite sheets for walking and flying
    if (game->dave.flying)
        daveSprite = spriteSheet->daveFlying;
    else
        daveSprite = spriteSheet->dave;

    // Choose sprite of the Dave's sheets according to its velocity
    if (game->dave.velocity.x > 0)
        spriteRect = (Rectangle){32, 32, 16, 16};
    else if (game->dave.velocity.x < 0)
        spriteRect = (Rectangle){32, 16, 16, 16};
    else
        spriteRect = (Rectangle){16, 0, 16, 16};

    // Drawing Dave's sprite
    Vector2 davePosition = {
        game->dave.position.x * TILE_SIZE, 
        game->dave.position.y * TILE_SIZE
    };
    DrawTextureRec(daveSprite, spriteRect, davePosition, WHITE);

    // Ending 2D camera context
    EndMode2D();

    // Drawing of the top bar. It is drawn after the stage to ensure that
    // it is always visible on the screen
    DrawRectangle(0, 0, TILE_SIZE * NUM_TILES_WIDTH, TILE_SIZE * TOP_BAR_TILES,
                  LIGHTGRAY);

    // Show current score on screen at top left corner
    char score[20];
    snprintf(score, 20, "PONTOS: %d", game->score);
    DrawText(score, TILE_SIZE * 0.5, TILE_SIZE * 0.8, TEXT_MAP_SIZE, BLACK);

    // Show remaining lives on screen
    char lifes[10];
    snprintf(lifes, 10, "VIDAS: %d", game->dave.lives);
    DrawText(lifes, TILE_SIZE * 9, TILE_SIZE * 0.8, TEXT_MAP_SIZE, MAROON);

    // Show current level on screen
    char level[15];
    snprintf(level, 16, "NÍVEL: %d", game->level);
    DrawText(level, TILE_SIZE * 16, TILE_SIZE * 0.8, TEXT_MAP_SIZE, BLACK);

    // Show icon on screen if Dave collects the trophy
    if (game->dave.gotTrophy) {
        DrawTexture(spriteSheet->trophy, 22 * TILE_SIZE, 0.8 * TILE_SIZE, GOLD);
        DrawText("Troféu", 23.5 * TILE_SIZE, 0.8 * TILE_SIZE, TEXT_MAP_SIZE, BLACK);
    }

    // Show message on screen if Dave acquires the jetpack
    if (game->dave.hasJetpack) {
        DrawText("Jetpack", TILE_SIZE * 30, TILE_SIZE * 0.8,
                 TEXT_MAP_SIZE, BLACK);
    }
    // Show message on screen if jetpack is active
    if (game->dave.flying) {
        DrawText("Jetpack", TILE_SIZE * 30, TILE_SIZE * 0.8,
                 TEXT_MAP_SIZE, RED);
    }

    EndDrawing();
}

/**
 * Create and configure a 2D camera based on game state
 * Arguments:
 *     game (Game*): Game to be displayed
 */
Camera2D getCamera(Game *game) {
    // Getting screen dimensions
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    // Calculating Dave center position on screen
    Vector2 daveCenter = Vector2Add(game->dave.position, (Vector2){0.5, 0.5});
    Vector2 daveScreenPos = Vector2Scale(daveCenter, TILE_SIZE);

    // Initial Camera configuration

    Camera2D camera = {0};
    // Camera always targets Dave position
    camera.target = daveScreenPos;
    // Show Dave at the center of the screen
    camera.offset = (Vector2){screenWidth / 2.0f, screenHeight / 2.0f};
    // Camera with no rotation
    camera.rotation = 0;
    // Camera zoom
    camera.zoom = 2;

    // Map extreme coordinates
    Vector2 topLeft = {0, 0};
    Vector2 bottomRight = {game->map.width, game->map.height};

    // Scaling vertices to their display position
    Vector2 scaledTopLeft = Vector2Scale(topLeft, TILE_SIZE);
    Vector2 scaledBottomRight = Vector2Scale(bottomRight, TILE_SIZE);

    // Actual positions of extreme vertices on the screen
    Vector2 topLeftScreen = GetWorldToScreen2D(scaledTopLeft, camera);
    Vector2 topRightScreen = GetWorldToScreen2D(scaledBottomRight, camera);

    // If the left border would appear on screen
    if (topLeftScreen.x > 0)
        // Change the offset to show only objects to the right of the border
        camera.offset.x = screenWidth / 2.0f - topLeftScreen.x;

    // If the top border would appear on screen
    if (topLeftScreen.y > TOP_BAR_TILES * TILE_SIZE)
        // Change the offset to show only objects below the border
        camera.offset.y = screenHeight / 2.0f - topLeftScreen.y + TOP_BAR_TILES * TILE_SIZE;

    // If the right border would appear on screen
    if (topRightScreen.x < screenWidth)
        // Change the offset to show only objects to the left of the border
        camera.offset.x = screenWidth + screenWidth / 2.0f - topRightScreen.x;

    // If the bottom border would appear on screen
    if (topRightScreen.y < screenHeight)
        // Change the offset to show only objects above the border
        camera.offset.y = screenHeight + screenHeight / 2.0f - topRightScreen.y;

    return camera;
}

/**
 * Draw Game Over screen
 * 
 * Arguments:
 *     game (Game*): Pointer to the game
 *     menu (Menu): Screen menu
 */
void renderGameOver(Game *game, Menu menu) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText("Fim de Jogo", TILE_SIZE * 3, TILE_SIZE * 3, HEADER_FONT_SIZE,
             BLACK);

    char score[40];
    snprintf(score, 40, "Sua pontuação: %d", game->score);
    DrawText(score, TILE_SIZE * 3, TILE_SIZE * 5, TEXT_FONT_SIZE, BLACK);

    drawMenu(menu, TILE_SIZE * 3, TILE_SIZE * 10);
    EndDrawing();
}

/**
 * Draw the record screen
 * 
 * Arguments:
 *     game (Game*): Pointer to the game
 *     username (char*): Current username text
 *     menu (Menu): Menu of the screen
 */
void renderScoreMenu(Game *game, char *username, Menu menu) {
    // Assembling score message
    char score[40];
    snprintf(score, 40, "Sua pontuação: %d", game->score);
    
    // Drawing screen
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText("Fim de Jogo", TILE_SIZE * 3, TILE_SIZE * 3, HEADER_FONT_SIZE,
             BLACK);

    DrawText(score, TILE_SIZE * 3, TILE_SIZE * 5, TEXT_FONT_SIZE, BLACK);

    DrawText("Parabéns! Sua pontuação está entre as 5 maiores.", TILE_SIZE * 3,
             TILE_SIZE * 8.5, 19, BLACK);
    DrawText("Digite seu username:", TILE_SIZE * 3, TILE_SIZE * 9.5,
             TEXT_FONT_SIZE, BLACK);

    DrawRectangleLines(TILE_SIZE * 3, TILE_SIZE * 11, 360, 30, BLACK);
    DrawText(username, (TILE_SIZE * 3) + 8, (TILE_SIZE * 11) + 8,
             TEXT_FONT_SIZE, BLACK);

    drawMenu(menu, TILE_SIZE * 3, TILE_SIZE * 13.5);
    EndDrawing();
}

/**
 * Draw a confirmation dialog at the center of the screen
 * 
 * Arguments:
 *     message (char*): message to be displayed
 *     menu (Menu): menu to be displayed inside the dialog
 */
void drawConfirmationDialog(char* message, Menu menu) {
    // Calculating dialog position
    int height = GetScreenHeight();
    int width = GetScreenWidth();
    int centerHeight = height / 2;
    int centerWidth = width / 2;
    Rectangle dialogBox = {centerWidth - 175, centerHeight - 75, 350, 150};

    // Dialog drawing
    BeginDrawing();
    DrawRectangle(dialogBox.x, dialogBox.y, dialogBox.width, dialogBox.height,
                  LIGHTGRAY);
    DrawText(message, dialogBox.x + 15, dialogBox.y + 30, TEXT_FONT_SIZE,
             BLACK);
    drawMenu(menu, dialogBox.x + 15, dialogBox.y + 30 + HEADER_FONT_SIZE);
    EndDrawing();
}

/**
 * Tear down and close the graphic resources
 * 
 * Arguments:
 *     spriteSheet (SpriteSheet*): sprite sheet to be unloaded
 */
void endGraphics(SpriteSheet* spriteSheet) {
    // Unloading all textures
    UnloadTexture(spriteSheet->wall);
    UnloadTexture(spriteSheet->dave);
    UnloadTexture(spriteSheet->crown);
    UnloadTexture(spriteSheet->ring);
    UnloadTexture(spriteSheet->gem);
    UnloadTexture(spriteSheet->gem2);
    UnloadTexture(spriteSheet->door);
    UnloadTexture(spriteSheet->doorClosed);
    UnloadTexture(spriteSheet->water);
    UnloadTexture(spriteSheet->fire);
    UnloadTexture(spriteSheet->daveFlying);
    UnloadTexture(spriteSheet->jetpack);

    // Closing window
    CloseWindow(); 
}
