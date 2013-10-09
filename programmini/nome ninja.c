/*
  Name: Pham Francesco - alias: Pnb2frank
  Date: 09/04/12 22.20
  Description: Il tuo nome ninja
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>

char *conversione(char carattere, char *pt);

int main(void)
{
     int i, x, termina;
     char nome[100], ninja[200];
     char *pt;
     
     do
     {
          /*inizializzazione*/
          nome[0] = '\0';
          ninja[0] = '\0';
          pt = ninja;
          
          /*Richiesta nome*/
          printf("__________IL TUO NOME NINJA__________ \n\n");
          printf("Inserisci il tuo nome reale: ");
          gets(nome);
          
          /*conversione in maiuscole*/
          for(i=0; nome[i] != '\0'; i++)
               nome[i]=toupper(nome[i]);
          
          /*conversione*/
          printf("\nIl tuo nome ninja e': ");
          for(i=0; nome[i] != '\0'; i++)
               pt = conversione(nome[i], pt);
          *pt = '\0';
               
          /*Visualizzazione*/
          printf("%s", ninja);
               
          /*Terminazione*/
          putchar('\n');
          putchar('\n');
          printf("Premi ESC per terminare \n");
          printf("Premi INVIO per ripetere \n");
          do
          {
               x = getch();
               if(x==13) //se x == ESC
               {
                    system("CLS");
                    termina = 0;
               }
               if(x==27)//se x == INVIO
                    termina = 1;
          }
          while(x!=13 && x!=27);
     }
     while(termina==0);
}

/*funzione di conversione caratteri*/
char *conversione(char carattere, char *pt)
{
     switch(carattere)
     {
          case 'A':
               *pt = 'K';
               *++pt = 'A';
               break;
          case 'B':
               *pt = 'Z';
               *++pt = 'U';
               break;
          case 'C':
               *pt = 'M';
               *++pt = 'I';
               break;
          case 'D':
               *pt = 'T';
               *++pt = 'E';
               break;
          case 'E':
               *pt = 'K';
               *++pt = 'U';
               break;
          case 'F':
               *pt = 'L';
               *++pt = 'U';
               break;
          case 'G':
               *pt = 'J';
               *++pt = 'I';
               break;
          case 'H':
               *pt = 'R';
               *++pt = 'I';
               break;
          case 'I':
               *pt = 'K';
               *++pt = 'I';
               break;
          case 'J':
               *pt = 'Z';
               *++pt = 'U';
               break;
          case 'K':
               *pt = 'M';
               *++pt = 'E';
               break;
          case 'L':
               *pt = 'T';
               *++pt = 'A';
               break;
          case 'M':
               *pt = 'R';
               *++pt = 'I';
               *++pt = 'N';
               break;
          case 'N':
               *pt = 'T';
               *++pt = 'O';
               break;
          case 'O':
               *pt = 'M';
               *++pt = 'O';
               break;
          case 'P':
               *pt = 'N';
               *++pt = 'O';
               break;
          case 'Q':
               *pt = 'K';
               *++pt = 'E';
               break;
          case 'R':
               *pt = 'S';
               *++pt = 'H';
               *++pt = 'I';
               break;
          case 'S':
               *pt = 'A';
               *++pt = 'R';
               *++pt = 'I';
               break;
          case 'T':
               *pt = 'C';
               *++pt = 'H';
               *++pt = 'I';
               break;
          case 'U':
               *pt = 'D';
               *++pt = 'O';
               break;
          case 'V':
               *pt = 'R';
               *++pt = 'U';
               break;
          case 'W':
               *pt = 'M';
               *++pt = 'E';
               *++pt = 'I';
               break;
          case 'X':
               *pt = 'N';
               *++pt = 'A';
               break;
          case 'Y':
               *pt = 'F';
               *++pt = 'U';
               break;
          case 'Z':
               *pt = 'Z';
               *++pt = 'I';
               break;
          default:
               exit(-1);
     }
     return ++pt;
}
