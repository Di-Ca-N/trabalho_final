/********************************************************
 * maps module
 * Loading of game maps
 ********************************************************/
#ifndef MAPS_H
#define MAPS_H

// ==== CONSTANTS ====
#define MAX_MAP_WIDTH 120 // Max supported map width
#define MAX_MAP_HEIGHT 30 // Max supported map height

// ==== TYPES ====

// Internal map representation
typedef struct{
    // Matrix map representation
    char stage[MAX_MAP_HEIGHT][MAX_MAP_WIDTH];

    // Dave starting position
    int daveStart[2];

    // Actual map dimensions
    int height;
    int width;
} Map;

// ==== FUNCTIONS ====
Map loadMap(char* filename); // Load a map from disk

#endif
