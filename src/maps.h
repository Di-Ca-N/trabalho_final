#ifndef MAPS_H
#define MAPS_H

#define MAX_MAP_WIDTH 120
#define MAX_MAP_HEIGHT 30

typedef struct{
    // Matrix map representation
    char stage[MAX_MAP_HEIGHT][MAX_MAP_WIDTH];

    // Dave starting position
    int daveStart[2];

    // Real map dimensions
    int height;
    int width;
} Map;

Map loadMap(char* filename);   // Load a map from disk
#endif
