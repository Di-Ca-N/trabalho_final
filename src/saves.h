/******************************************************
 * saves module
 * Game saves management
 ******************************************************/
#ifndef SAVES_H
#define SAVES_H

#include "game.h"

// ==== CONSTANTS ====
// Path to save games
#define SAVE_PATH "assets/save.dat"

// ==== FUNCTIONS ====
Game loadGame();           // Load a save from disk
void saveGame(Game game);  // Save a game to disk

#endif
