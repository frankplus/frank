#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>

const int MaxStr = 20;

int main(void)
{
     long double res=0;
     char str[MaxStr], *pnt;
     
     str[0] = '\n';
     
     printf("Calcolatrice v1 \n\n");
     system("PAUSE");
     system("CLS");
     
     for(;;)
     {
          pnt = str;
          while(*pnt != '\n') pnt++;
          gets(pnt);
          system("CLS");
          res = calcola(str);
          printf("%LG", res);
          sprintf(str, "%Lf\n", res);
     }
     
     return 0;
}

long double calcola(char* str)
{
     
}
