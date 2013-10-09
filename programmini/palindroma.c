#include <stdio.h>
#include <stdlib.h>

int main()
{
     int stopstr, i, j, esito;
     char str[100];
     printf("Inserisci parola palindroma: ");
     scanf("%s", str);
     
     for(stopstr=0; str[stopstr] != '\0'; stopstr++); //cerca fine stringa
     
     /*controllo se è un palindroma*/
     for(i=0, j=stopstr-1; j>0;)
     {
          if(str[i] == str[j])
          {
               i++;
               j--;
          }
          else
          {
               esito = 0;
               break;
          }
     }
     
     if(j==0)
          esito = 1;
     
     /*Mostra l'esito*/
     switch(esito)
     {
          case 0:
               printf("Non e' un palindroma! \n");
               break;
          case 1:
               printf("E' un palindroma! \n");
               break;
          default:
               printf("ERROR!!! \n");
     }
     system("PAUSE");
}
