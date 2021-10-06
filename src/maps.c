#include "maps.h"
#include <stdio.h>
#include <stdlib.h>

Map loadMap(char* filename) {
   
    Map newMap;

    FILE *file; 
    file = fopen (filename , "r"); 

    if (file == NULL) {
        printf ("Erro no carregamento do arquivo\n"); 
        getchar();
        exit(0); 
    }

    char mapa1[2];
    int x = 0, y = 0;
    while (fgets (mapa1, 2 , file) != NULL ) { 
        printf ("%s" , mapa1);

        if (mapa1[0] == 'D') {
            newMap.daveStart[0] = y;
            newMap.daveStart[1] = x;
            newMap.stage[y][x] = ' ';
        } else if (mapa1[0] != '\n') {
            newMap.stage[y][x] = mapa1[0];
        }


        if(mapa1[0] == '\n') {
            y++;
            x = 0;
        } else {
            x++;
        }
    }

    fclose(file);

    printf ("\n");


    return newMap;
}
