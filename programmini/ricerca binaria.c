#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXLENGTH 10000

int ricerca(int, int*, int);

int main()
{
     int valore, array[MAXLENGTH], pos, i;
     for(i=0; i<MAXLENGTH; i++)
          array[i] = i;
     
     printf("Inserisci valore da ricercare: ");
     scanf("%d", &valore);
     
     pos = ricerca(valore, array, MAXLENGTH);
     
     if(pos==-1)
          printf("Il valore non e' presente! \n");
     else
          printf("il valore e' presente in posizione: %d \n", pos);
     
     system("PAUSE");
}

int ricerca(int x, int *array, int length)
{
     int alto, basso, pos;
     
     basso = 0; 
     alto = length-1;

     while(alto>basso)
     {
          pos = (alto+basso)/2;
          if( *(array+pos) == x)  return pos;
          else
               if(*(array+pos)<x) 
               basso = pos+1;
               else
               alto = pos-1;
     }
     
     
     return -1;
}
