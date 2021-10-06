#include "maps.h"
#include <stdio.h>
#include <stdlib.h>

Map loadMap(char* filename) {
   
    printf(filename);
    Map newMap;
    newMap.height = 10;
    // Ler arquivo

    FILE *arq;
    int result;
    char Str[50];
    arq = fopen (filename, "rt");
    if (arq == NULL) 
    {
      printf ("Problemas na criacao do arquivo \n");
      return;
    }
    // Fim da leitura

    return newMap;
}

