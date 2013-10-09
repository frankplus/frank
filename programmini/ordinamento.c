#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_LENGTH 1000

int main()
{
     int length, i, x, min, oux, array[MAX_LENGTH];
     
     array[999] = INT_MAX;
     
     printf("Inserisci lunghezza dell'array: ");
     scanf("%d", &length);
     
     for(i=0; i<length; i++)
     {
          printf("array[%d] = ", i);
          scanf("%d", &array[i]);
     }
     for(x=0; x<length; x++)
     {
          min = 999;
          for(i=x; i<length; i++)
               if(array[i] < array[min])
                    min = i;
          
          oux = array[x];
          array[x] = array[min];
          array[min] = oux;
     }
     
     printf("\narray risultante: \n");
     for(i=0; i<length; i++)
          printf("array[%d] = %d \n", i, array[i]);
          
     system("PAUSE");
     return 0;
}
