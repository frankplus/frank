/*
  Name: Run Length Encoding
  Copyright: Open-source
  Author: Pham Francesco (alias pnb2frank)
  Date: 30/03/12 16.50
  Description: Run Length Encoding: algoritmo di compressione degli array.
               Prende in input un array e da come array risultante gli elementi 
               e le volte che sono ripetute.
*/

#include <stdio.h>

int main()
{
    int i, j, count, array[10], res[10][2];
    
    /*Inizializzazione dell' array*/
    for(i=0; i<10; i++)
    {
        array[i] = 0;
    }
    
    /*Inizializzazione di res*/
    for(i=0; i<10; i++)
    {
          res[i][0]=0;
          res[i][1]=0;
     }
    
    /*Richiesta valori*/
    for(i=0; i<10; i++)
    {
          printf("array[%d]= ", i);
          scanf("%d", &array[i]);
     }
    
    /*generazione array res*/
    count = 1;
    j = 0;
    for(i=0; i<10; i++)
    {
          if(array[i] == array[i+1])
               count++;
          else
          {
               res[j][0] = array[i]; //assegna il valore
               res[j][1] = count;    //indica le colte ripetute
               j++;
               count = 1;
          }
    }
    
    /*Visualizzazione array risultante*/
    printf("res={");
    for(i=0; i<10; i++)
          if(res[i][0] != 0 && res[i][1] != 0)
               printf("(%d,%d)", res[i][0], res[i][1]);
    printf("} \n");
    
    getchar();
    getchar();
    
    return 0;
}
