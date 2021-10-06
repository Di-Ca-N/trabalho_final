#include "maps.h"
#include <stdio.h>
#include <stdlib.h>

Map loadMap(char* filename) {
   
 

int main(void) {

  FILE *file; 
  file = fopen ("mapanivel1.txt" , "r" ); 

  if (file == NULL) {
    printf ("Erro no carregamento do arquivo\n"); 
    getchar();
    system ("pause"); // para vermos o andamento do programa
    exit(0); // fim do arquivo. Semelhante a return 0;
  }
    // Estaremos lendo texto (strings) , nesse caso, pois mapanivel1 é composto por caracteres. Então precisamos criar uma variável para "armazenar" esses caracteres

   char mapa1[2];

   while (fgets (mapa1, 2 , file) != NULL ) { // a função while está indo até o arquivo de texto e pegando os caracteres que estão lá. Fará isso, até que não tenha mais nada lá para ser pego (poderia, além de ser caracteres, ser números, etc.). Porém, nesses casos, precisamos usar comandos para converter os números etc. para strings
     printf ("%s" , mapa1);                  // se não usássemos o while, colocando apenas fgets (frase, 100, file); leria apenas a primeira linha, pois fgets lê todos os caracteres até encontrar a quebra de linha. Como colocamos o while, o fgets continuará lendo após a troca de linha

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


   return 0;
}
