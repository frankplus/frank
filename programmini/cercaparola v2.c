#include <stdio.h>
#include <stdlib.h>

int trova(const char *str1,const char *str2)
{
    const char* ptr1;
    const char* ptr2;
    /*ricerca*/
    for( ptr1=str1, ptr2=str2; *ptr2 != '\0'; ptr2++ )
    {
         if( *ptr1 == '\0' )
              return 1;
         else
         {    if( *ptr1 == *ptr2 )
              {
                   ptr1++;
              }
              else
              {
                   ptr1 = str1;
              }
         }
    }
    
    return 0;
}

int main(void)
{
    int trovato;
    char stringa1[100]="enrico";
    char stringa2[100]="ciao enrico come stai";

    
    trovato = trova(stringa1, stringa2); //trova stringa1 in stringa2
    
    switch(trovato)
    {
         case 0:
              printf("Non e' presente! \n");
              break;
         case 1:
              printf("E' presente! \n");
              break;
    }
    
    system("PAUSE");
}
