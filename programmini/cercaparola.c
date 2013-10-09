#include <stdio.h>
#include <stdlib.h>

int main()
{
     int i, j, inizio;
     int trovato = 0;
     char frase[100];
     char parola1[100];
     char parola2[100];
     
     printf("Inserisci una frase: ");
     gets(frase);
     
     printf("Inserisci parola da ricercare nella frase: ");
     gets(parola1);
     
     printf("Inserisci parola che sostituire: ");
     gets(parola2);
     
     /*ricerca della parola*/
     for(i=0,j=0; i<100 && trovato==0;)
     {
          if(parola1[j] == '\0')
               trovato=1;
          else 
          {    if(parola1[j] == frase[i])
               {
                    if(j==0) inizio=i;
                    i++;
                    j++;
               }
               else
               {
                    i++;
                    j=0;
               }
          }
     }
     
     /*Sostituzione della parola*/
     if(trovato==0)
          printf("la parola non c'e' nella frase");
     else
     {
          i = inizio;
          for(j=0; parola2[j] != '\0'; j++,i++)
          {
               frase[i] = parola2[j];
          }
          frase[i] = '\0';
          printf("%s", frase);

     }
     
     getchar();
     return 0;
}
