#ifndef SAVES_H
#define SAVES_H

#include "game.h"

Game loadSave(char* savePath);
void saveGame(Game game, char* path);

#endif
