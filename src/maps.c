#include "maps.h"
#include <stdio.h>
#include <stdlib.h>

Map loadMap(char* filename) {
   
   Map newmap;

  FILE *file; 
  file = fopen (filename , "r" ); 

  if (file == NULL) {
    printf ("Erro no carregamento do arquivo\n"); 
    getchar();
    exit(0); 
  }
    

   char mapa[2];

   while (fgets (mapa, 2 , file) != NULL ) { 
     printf ("%s" , mapa);                 

//        if(mapa1[0] == 'D') {
//            meu_mapa.daveStart[0] = x;
//            meu_mapa.daveStart[1] = y;
//        }
//        if(mapa1[0] == '\n') {
//            y++;
//        }
   }

   fclose(file);

   printf ("\n");


   return newmap;
}
