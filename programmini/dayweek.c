#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int tabella_mese(int);
int bisestile();
int tabella_anno(int);
void errore();

int main()
{
     int gg, mm, ss, aa;
     int G, M, A, C;
     int x, termina, risultato;
     
     do
     {
          system("CLS");
          printf("QUESTO PROGRAMMA TROVA IL GIORNO DELLA SETTIMANA DELLA DATA INSERITA..\n\n");
          printf("data (gg/mm/aaaa): ");
          scanf("%d/%d/%2d%2d", &gg, &mm, &ss, &aa);
          
          G = gg % 7;
          M = tabella_mese(mm);
          A = aa % 28 + (aa % 28 - 1)/4;
          C = tabella_anno(ss%4);
          
          //printf("%02d/%02d/%02d%02d", gg, mm, ss, aa);
          //printf("G = %d \nM = %d \nA = %d \nC = %d", G, M, A, C);
          
          risultato = (G + M + A + C) % 7;
          if(bisestile() == 1 && mm > 2)
               risultato++;
          
          printf("\n\nIL GIORNO DELLA SETTIMANA E'... ");
          switch(risultato)
          {
               case 0:
                    printf("Domenica!");
                    break;
               case 1:
                    printf("Lunedi!");
                    break;
               case 2:
                    printf("Martedi!");
                    break;
               case 3:
                    printf("Mercoledi!");
                    break;
               case 4:
                    printf("Giovedi!");
                    break;
               case 5:
                    printf("Venerdi!");
                    break;
               case 6:
                    printf("Sabato!");
                    break;
               default:
                    errore();
          }
          
          do
          {
               termina = -1;
               printf("\n\nPremi INVIO per ripetere... \n");
               printf("Premi ESC per uscire... \n");
               x = getch();
               if(x == 27)
                    termina = 1;
               else if(x == 13)
                    termina = 0;
          }
          while(termina == -1);
     }
     while(termina == 0);
     return 0;
}

int tabella_mese(int mese)
{
     int res;
     
     switch(mese)
     {
          case 1:
               if(bisestile())
                    res = 6;
               else
                    res = 0;
               break;
          case 2:
               if(bisestile())
                    res = 2;
               else
                    res = 3;
               break;
          case 3:
               res = 3;
               break;
          case 4:
               res = 6;
               break;
          case 5:
               res = 1;
               break;
          case 6:
               res = 4;
               break;
          case 7:
               res = 6;
               break;
          case 8:
               res = 2;
               break;
          case 9:
               res = 5;
               break;
          case 10:
               res = 0;
               break;
          case 11:
               res = 3;
               break;
          case 12:
               res = 5;
               break;
          default:
               errore();
     }
     return res;
}

int bisestile()
{
     if(intanno % 4 == 0 && (intanno % 100 != 0 || intanno % 400 == 0))
          return 1;
     else
          return 0;
}

int tabella_anno(int modulo)
{
     int res;
     switch(modulo)
     {
          case 0:
               res = 6;
               break;
          case 1:
               res = 4;
               break;
          case 2:
               res = 2;
               break;
          case 3:
               res = 0;
               break;
          default:
               errore();
     }
     return res;
}

void errore()
{
     system("CLS");
     printf("OOPS... C'E' UN ERRORE INASPETTATO \n\n");
     printf("forse hai dimenticato di digitare gli zeri \n");
     printf("nelle date minori di 10 es. 05/04/2012 NON 5/4/2012 \n");
     printf("oppure hai inserito una data invalida es.34/13/9999 \n");
     printf("Se non rientra negli errori sopra elencati \n");
     printf("avvisare lo sviluppatore: Pham Francesco \n\n");
     
     system("PAUSE");
     exit(0);
}
