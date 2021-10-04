#include "saves.h"
#include <stdio.h>

Game loadGame() {
    // If save does not exist, load a new game
    if (!FileExists(SAVE_PATH)) {
        return newGame();
    }
    // Load save file
    FILE *saveFile = fopen(SAVE_PATH, "rb");
    Game game;

    // Read file and put data into game variable
    fread(&game, sizeof(Game), 1, saveFile);
    
    // Close save file
    fclose(saveFile);

    return game;
}

void saveGame(Game game) {
    FILE *saveFile = fopen(SAVE_PATH, "wb");
    fwrite(&game, sizeof(Game), 1, saveFile);
    fclose(saveFile);
}
