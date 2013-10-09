#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <windows.h>

#define LUNGHEZZA 8

void print(int dist1, int dist2, int balx, int baly);

int main(void)
{
     int dist1=8, dist2=8, termina=0, balx, baly, direzione=1;
     
     balx = 44;
     baly = LUNGHEZZA;
     
     while(termina == 0)
     {
          Sleep(30);
          if(direzione == 1)
               balx+=3;
          else if(direzione == 2)
               balx-=3;
               
          print(dist1, dist2, balx, baly);
          
          if(kbhit())
          {
               switch(getch())
               {
                    case '8':
                         if(dist2-1 > 0)
                              dist2--;
                         break;
                    case '2':
                         if(dist2+1 <= 23-LUNGHEZZA)
                              dist2++;
                         break;
                    case 'a':
                    case 'A':
                         if(dist1-1 > 0)
                              dist1--;
                         break;
                    case 'z':
                    case 'Z':
                         if(dist1+1 <= 23-LUNGHEZZA)
                              dist1++;
                         break;
                    case 27:
                         termina=1;
               }
          }
     }
     
     system("PAUSE");
}

void print(int dist1, int dist2, int balx, int baly)
{
     int i;
     
     system("CLS");
     for(i=1,dist1; i<=LUNGHEZZA; i++,dist1++)
     {
          gotoxy(6,dist1);
          putchar('\333');
     }
     
     for(i=1,dist2; i<=LUNGHEZZA; i++,dist2++)
     {
          gotoxy(75,dist2);
          putchar('\333');
     }
     
     gotoxy(balx, baly);
     putchar('\333');
     
     gotoxy(1, 23);
     for(i=1; i<=80; i++)
          putchar('_');
}
