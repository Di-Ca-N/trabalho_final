#include "graphics.h"

#include <stdio.h> // sprintf
#include "raylib.h"

void initGraphics() {
    // Init game window
    InitWindow(TILE_SIZE * NUM_TILES_WIDTH, TILE_SIZE * NUM_TILES_HEIGHT, "Dangerous Dave");

    // Set game to run at 60 fps
    SetTargetFPS(60);

    // Remove default exit key
    SetExitKey(0);
}

// Render a menu into screen
void renderMenu(Menu menu) {
    // Start drawing
    BeginDrawing();

    // Clear background
    ClearBackground(RAYWHITE);
    
    // Draw menu title
    DrawText("Dangerous Dave", 100, 100, 30, BLACK);

    // Loop to draw menu options
    for (int i = 0; i < menu.numOptions; i++) {
        // Buffer to hold option text. Set to MAX_OPTION_LENGTH + 2 to account for extra
        // characters added to the buffer on the "if" below
        char optionBuffer[MAX_OPTION_LENGTH + 2];

        // If the option being current redendered is the selected option
        if (menu.selectedOption == i) {
            // Add a marker to the option
            snprintf(optionBuffer, MAX_OPTION_LENGTH + 2, "> %s", menu.options[i]);
        } else {
            // Otherwise, add no mark
            snprintf(optionBuffer, MAX_OPTION_LENGTH + 2, "  %s", menu.options[i]);
        }
        // Draw option text to screen
        DrawText(optionBuffer, 100, 140 + i * 22, 20, BLACK);
    }

    // End drawing
    EndDrawing();
}

void endGraphics() {
    CloseWindow();
}