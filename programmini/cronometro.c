#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main(void)
{
     int min, sec, cent;
     
     printf("CRONOMETRO PRECISISSIMO !!! \n");
     
     for(min=0; min<60; min++)
          for(sec=0; sec<60; sec++)
               for(cent=0; cent<100; cent++)
               {
                    Sleep(10);
                    gotoxy(1, 4);
                    printf("%d : %d : %02d", min, sec, cent);
                    if(kbhit())
                    {
                         if(getch()==8)
                         {
                              min=0;
                              sec=0;
                              cent=0;
                              printf("\nCronometro azzerato.");
                         }
                         putchar('\n');
                         system("PAUSE");
                         system("CLS");
                    }
               }
}
