#include "saves.h"

#include <stdio.h>

int saveExists() {
    return FileExists(SAVE_PATH);
}

// Load a game save from disk
Game loadGame() {
    // Load save file
    FILE *saveFile = fopen(SAVE_PATH, "rb");

    // If the save file can't be open, create and return a new game
    if (saveFile == NULL) {
        printf("Cannot open save file. Creating a new game\n");
        return newGame();;
    }

    Game game;

    // Read file and put data into game variable
    fread(&game, sizeof(Game), 1, saveFile);
    
    // Close save file
    fclose(saveFile);

    return game;
}

// Save a game to the disk
void saveGame(Game game) {
    // Reset Dave speed before save. The speeds must be recalculated
    // every time the game is loaded
    game.dave.speed.x = 0;
    game.dave.speed.y = 0;

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
