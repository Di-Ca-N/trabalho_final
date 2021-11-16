#include "maps.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * Load a map file from disk. A map file is expected to be a text file
 * containing only the characters defined as constants in map.h file. 
 * Also, it must have valid dimensions and the last line should not 
 * contain characters.
 * 
 * Arguments:
 *     filename (char*): Filename of the map to be loaded    
 */
Map loadMap(char *filename) {
    // Trying to open map file
    FILE *file;
    file = fopen(filename, "r");
    if (file == NULL) {
        // Error message - Load failed
        printf("Load failed\n");
        exit(0);
    }

    // Creating new map with default options
    Map newMap;
    newMap.width = 0;
    newMap.height = 0;

    // Line and column counters
    int l = 0, c = 0;

    // Reading map informations until eof
    while (!feof(file)) {
        char chr = getc(file);

        if (chr != EOF) {
            if (chr == DAVE) {
                // Dave starting position - line (l) and column (c)
                newMap.daveStart[0] = l;
                newMap.daveStart[1] = c;
                // Remove Dave from the stage.
                newMap.stage[l][c] = ' ';
            } else if (chr != '\n') {
                // Every other char (except \n) is written to the map 
                // matrix
                newMap.stage[l][c] = chr;
            }

            // When a new line is found
            if (chr == '\n') {
                // Increase line counter and reset the column counter
                l++;
                c = 0;
            } else {
                // In every other case, just increment the column counter
                c++;
            }
        }
        // Map width should be the width of the longest line
        if (newMap.width < c) {
            newMap.width = c;
        }
    }
    // Saving map height
    newMap.height = l;

    // Closing map file
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