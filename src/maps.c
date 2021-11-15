#include "maps.h"

#include <stdio.h>
#include <stdlib.h>

// Loading a map from disk
Map loadMap(char *filename) {
    Map newMap;
    FILE *file;
    file = fopen(filename, "r");
    if (file == NULL) {
        // Error message - Load failed
        printf("Load failed\n");
        exit(0);
    }

    newMap.width = 0;
    newMap.height = 0;
    int l = 0, c = 0;
    // Reading map informations
    while (!feof(file)) {
        char chr = getc(file);

        if (chr != EOF) {
            if (chr == DAVE) {
                // Dave starting position - line (l) and column (c)
                newMap.daveStart[0] = l;
                newMap.daveStart[1] = c;
                newMap.stage[l][c] = ' ';
            } else if (chr != '\n') {
                newMap.stage[l][c] = chr;
            }

            if (chr == '\n') {
                l++;
                c = 0;
            } else {
                c++;
            }
        }
        // Map width should be the width of the longest line
        if (newMap.width < c) {
            newMap.width = c;
        }
    }
    // Actual Map height (part of Max Supported map width)
    newMap.height = l + 1;

    fclose(file);

    return newMap;
}

/**
 * Return the character located on some position of the stage
 *
 * Arguments:
 *     map (Map*): Pointer to the map to get position
 *     x (float): x position of the wanted character
 *     y (float): y position of the wanted character
 */
char getStagePosition(Map *map, float x, float y) {
    return map->stage[(int)y][(int)x];
}

/**
 * Set the character located on some position of the stage to a new
 * value
 *
 * Arguments:
 *     map (Map*): Pointer to the map to get position
 *     x (float): x position of the wanted character
 *     y (float): y position of the wanted character
 */
void clearStagePosition(Map *map, float x, float y) {
    map->stage[(int)y][(int)x] = ' ';
}