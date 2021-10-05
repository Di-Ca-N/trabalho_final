/******************************************************
 * graphics module
 * Definitions and drawing of game screens and elements
 ******************************************************/

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "game.h"
#include "ranking.h"
#include "menus.h"

// ==== CONSTANTS ====
#define TILE_SIZE 16         // Size (in pixels) of a single game tile
#define NUM_TILES_HEIGHT 20  // Number of tiles in the height of the window
#define NUM_TILES_WIDTH 35   // Number of tiles in the width of the window
#define HEADER_FONT_SIZE 30  // Font size of headers
#define TEXT_FONT_SIZE 21    // Font size of text


// ==== FUNCTIONS ====
void initGraphics();                            // Init graphics module
void endGraphics();                             // Tear down graphics
void renderGame(Game game);                     // Draw the game
void renderMainMenu(Menu menu);                 // Draw the main menu
void renderRanking(Ranking ranking, Menu menu); // Draw the ranking

#endif
