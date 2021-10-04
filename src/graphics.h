#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "game.h"
#include "ranking.h"

#define TILE_SIZE 16
#define NUM_TILES_HEIGHT 20
#define NUM_TILES_WIDTH 35
#define HEADER_FONT_SIZE 30
#define TEXT_FONT_SIZE 21

void initGraphics();                             // Init graphics module
void renderGame(Game game);                      // Render game to scren
void renderMainMenu(Menu menu);                      // Render menu to screen
void renderRanking(Ranking ranking, Menu menu);  // Render ranking to screen
void endGraphics();                              // Tear down graphics

#endif
