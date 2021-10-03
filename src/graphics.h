#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "raylib.h"

#include "game.h"
#include "ranking.h"

void renderGame(Game game);           // Render game to scren
void renderMenu(Menu menu);           // Render menu to screen
void renderRanking(Ranking ranking);  // Render ranking to screen

#endif
