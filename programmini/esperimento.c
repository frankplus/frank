#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
    
  /*dichiarazioni*/
  int i, somma, casuale, pre_casuale, media;
  
  i=1;
  somma=0;
  casuale=0;
  pre_casuale=0;
  
  
  while(i <= 150) {
            pre_casuale = casuale; //serve solo per controllo della variazione di casuale
            srand(time(NULL));
            casuale = rand() % 150 + 1;
            
            /*esegue if solo se è stato generato un'altro valore casuale*/
            if(pre_casuale != casuale) {
                           somma += casuale;
                           printf("i = %d, somma =%d\n", i, somma);
                           i++;
                           }
          
  
  }
  
  media = somma/150;
  printf("la media e': %d %", media);
  
  if(media==50)
              printf("esperimento riuscito!!! \n");
  else
              printf("esperimento non riuscito :( \n");
  
  system("PAUSE");	
  return 0;
}
