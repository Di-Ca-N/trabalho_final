#include "saves.h"

#include <stdio.h>

// Load a game save from disk
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

// Save a game to the disk
void saveGame(Game game) {
    // Reset Dave speed before save. The speeds must be recalculated
    // every time the game is loaded
    game.dave.speed.x = 0;
    game.dave.speed.y = 0;

    // Open save file
    FILE *saveFile = fopen(SAVE_PATH, "wb");

    // Write game to file
    fwrite(&game, sizeof(Game), 1, saveFile);

    // Close file
    fclose(saveFile);
}
