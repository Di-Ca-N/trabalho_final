/********************************************************
 * maps module
 * Loading of game maps
 ********************************************************/
#ifndef MAPS_H
#define MAPS_H

// ==== CONSTANTS ====
#define MAX_MAP_WIDTH 120 // Max supported map width
#define MAX_MAP_HEIGHT 30 // Max supported map height

#define WALL 'x'
#define TROPHY 'T'
#define WATER 'A'
#define FIRE 'F'
#define DAVE 'D'
#define DOOR 'P'
#define ENTRY 'O'
#define JETPACK 'J'
#define RING '$'
#define CROWN '%'
#define RUBY '#'
#define SAPHIRE '@'
#define AMETHYST '!'

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
