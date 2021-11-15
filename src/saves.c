#include "saves.h"

#include <stdio.h>

/**
 * Load a game save from disk
 */
Game loadGame() {
    // Load save file
    FILE *saveFile = fopen(SAVE_PATH, "rb");

    // If the save file can't be open, create and return a new game
    if (saveFile == NULL) {
        printf("Cannot open save file. Creating a new game\n");
        return newGame(loadMap("assets/stages/fase_01.txt"));
    }

    Game game;

    // Read file and put data into game variable
    fread(&game, sizeof(Game), 1, saveFile);

    // Close save file
    fclose(saveFile);

    return game;
}

/**
 * Save a game to the disk.
 *
 * Arguments:
 *     game (Game): Game to be saved
 */
void saveGame(Game game) {
    // Release all actions before save
    releaseAllActions(&game);

    // Open save file
    FILE *saveFile = fopen(SAVE_PATH, "wb");

    if (saveFile == NULL) {
        printf("Cannot save game\n");
        return;
    }

    // Write game to file
    fwrite(&game, sizeof(Game), 1, saveFile);

    // Close file
    fclose(saveFile);
}
