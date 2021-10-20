#include "maps.h"
#include <stdio.h>
#include <stdlib.h>

Map loadMap(char *filename)  // Loading a map from disk
{
    Map newMap;
    FILE *file;
    file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Erro no carregamento do arquivo\n");  // Error message - Load failed
        getchar();
        exit(0);
    }

    char mapa[2];

    int l = 0, c = 0;
    while (fgets(mapa, 2, file) != NULL)  // Reading map informations
    {

        if (mapa[0] == 'D')
        {                                 // Dave starting position - line (l) and columm (c)
            newMap.daveStart[0] = l;
            newMap.daveStart[1] = c;
            newMap.stage[l][c] = ' ';
        }
        else if (mapa[0] != '\n')
        {                                
            newMap.stage[l][c] = mapa[0]; 
        }

        if (mapa[0] == '\n')
        {
            l++;
            c = 0;
        }
        else
        {
            c++;
        }
    }
    newMap.width = c; // Actual Map width (part of Max Supported map height)
    newMap.height = l + 1; // Actual Map height (part of Max Supported map width)

    fclose(file);

    return newMap; 
}
