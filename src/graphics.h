/******************************************************
 * graphics module
 * Definitions and drawing of game screens and elements
 ******************************************************/

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "game.h"
#include "ranking.h"
#include "menus.h"

// ==== TYPES ====

// Sprite sheet containing all game objects
typedef struct {
    Texture2D wall;
    Texture2D dave;
    Texture2D daveFlying;
    Texture2D crown;
    Texture2D gem;
    Texture2D gem2;
    Texture2D ring;
    Texture2D trophy;
    Texture2D door;
    Texture2D doorClosed;
    Texture2D fire;
    Texture2D water;
    Texture2D jetpack;
} SpriteSheet;

// ==== CONSTANTS ====
#define TILE_SIZE 16         // Size (in pixels) of a single game tile
#define NUM_TILES_HEIGHT 25  // Number of tiles in the height of the window
#define NUM_TILES_WIDTH 40   // Number of tiles in the width of the window
#define HEADER_FONT_SIZE 30  // Font size of headers
#define TEXT_FONT_SIZE 21    // Font size of text
#define TEXT_MAP_SIZE 18     // Font size of text on the game screen
#define TOP_BAR_TILES 2      // Number of tiles on the top bar

// ==== FUNCTIONS ====
void initGraphics(SpriteSheet* spriteSheet);    // Init graphics module
void endGraphics(SpriteSheet* SpriteSheet);     // Tear down graphics
void renderGame(Game* game, SpriteSheet* spriteSheet); // Draw the game screen
void renderMainMenu(Menu menu);                 // Draw the main menu screen
void renderRanking(Ranking ranking, Menu menu); // Draw the ranking screen
void renderGameOver(Game* game, Menu menu);     // Draw the game over screen
void renderRecord(Game *game, char *username, Menu menu); // Draw the record screen
void drawConfirmationDialog(char* message, Menu menu); // Draw confirmation dialog

#endif
