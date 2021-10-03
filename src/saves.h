#ifndef SAVES_H
#define SAVES_H

#include "game.h"

Game loadSave(char* savePath);         // Load a save from disk
void saveGame(Game game, char* path);  // Save a game to disk

#endif
