#ifndef SAVES_H
#define SAVES_H

#include "game.h"

#define SAVE_PATH "assets/save.dat"

Game loadSave();           // Load a save from disk
void saveGame(Game game);  // Save a game to disk

#endif
