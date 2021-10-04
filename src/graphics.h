#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "game.h"
#include "ranking.h"

#define TILE_SIZE 16
#define NUM_TILES_HEIGHT 20
#define NUM_TILES_WIDTH 35

void initGraphics();                  // Init graphics module
void renderGame(Game game);           // Render game to scren
void renderMenu(Menu menu);           // Render menu to screen
void renderRanking(Ranking ranking);  // Render ranking to screen
void endGraphics();                   // Tear down graphics

#endif
