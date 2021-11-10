/********************************************************
 * maps module
 * Loading of game maps
 ********************************************************/
#ifndef MAPS_H
#define MAPS_H

// ==== CONSTANTS ====
#define MAX_MAP_WIDTH 120 // Max supported map width
#define MAX_MAP_HEIGHT 30 // Max supported map height

// Recognized map characters
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

// Map representation
typedef struct{
    // Stage matrix
    char stage[MAX_MAP_HEIGHT][MAX_MAP_WIDTH];

    // Dave starting position
    int daveStart[2];

    // Actual map dimensions
    int height;
    int width;
} Map;

// ==== FUNCTIONS ====
Map loadMap(char* filename);                         // Load a map from disk
char getStagePosition(Map *map, float x, float y) ;  // Return the char at some position
void clearStagePosition(Map *map, float x, float y); // Clear the char at some position

#endif
