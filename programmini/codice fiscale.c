#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>

int ctrl_consonante(char x);
int ctrl_vocale(char x);
char charmese(int x);

char cognome[30];
char nome[30];
char comune[30];
char anno[4];
int mese;
int giorno;
char sesso;

int i, j, c;
int car;
int ncons;

int main(int argc, char *argv[])
{   
     printf("PROGRAMMA PER LA GENERAZIONE DEL CODICE FISCALE \n\n");
     
     printf("Inserisci il cognome: ");
     gets(cognome);
     
     printf("Inserisci il nome: ");
     gets(nome);
     
     printf("Inserisci data di nascita (gg/mm/aaaa): ");
     scanf("%d/%d/%s", &giorno, &mese, anno);
     
     /*printf("Inserisci comune di nascita: ");
     gets(comune);*/
     
     printf("Inserisci sesso (M o F): \n");
     sesso = getch();
     
     /*trasforma le lettere nelle rispettive maiuscole*/
     for(i=0; i<30; i++)
          cognome[i]=(toupper(cognome[i]));
     for(i=0; i<30; i++)
          nome[i]=(toupper(nome[i]));
     sesso=(toupper(sesso));
     
     printf("\n%s, %s, %s, %d, %d, %c \n", cognome, nome, anno, mese, giorno, sesso);
     
     printf("\nil tuo codice fiscale e': ");
     /*------------------PARTE DEL COGNOME-------------------*/
     car = 1;
     
     /*scrive le 3 consonanti*/
     for(i=0; i<30 && car<=3; i++)
     {
          if(ctrl_consonante(cognome[i]))
          {
               printf("%c", cognome[i]);
               car++;
          }
     }
     
     /*se le consonanti non bastano scrive le vocali*/
     for(i=0; i<30 && car<=3; i++)
     {
          if(ctrl_vocale(cognome[i]))
          {
               printf("%c", cognome[i]);
               car++;
          }
     }
     
     /*Se il cognome ha meno di 3 lettere mette delle X*/
     for(; car<=3; car++)
          printf("X");
     
     /*-------------------PARTE DEL NOME-------------------*/
     car = 1;
     ncons = 0;
     j=1;
     
     /*conta numero consonanti*/
     for(i=0; i<30; i++)
     {
          if(ctrl_consonante(nome[i]))
               ncons++;
     }
     
     /*se il nome contiene quattro o più consonanti, 
     si scelgono la prima, la terza e la quarta, 
     altrimenti le prime tre in ordine.*/
     if(ncons >= 4)
     {
          for(i=0; i<30; i++)
          {
               if(ctrl_consonante(nome[i]))
               {
                    if(j==1 || j==3 || j==4)   
                    {  
                         printf("%c", nome[i]);
                         car++;
                    }
                    j++;
               }
          }
     }
     else
     {
          for(i=0; i<30 && car<=3; i++)
          {
               if(ctrl_consonante(nome[i]))
               {
                    printf("%c", nome[i]);
                    car++;
               }
          }
     }
     
     /*se le consonanti non bastano scrive le vocali*/
     for(i=0; i<30 && car<=3; i++)
     {
          if(ctrl_vocale(nome[i]))
          {
               printf("%c", nome[i]);
               car++;
          }
     }
     
     /*Se il nome ha meno di 3 lettere mette delle X*/
     for(; car<=3; car++)
          printf("X");
          
     /*-------------------PARTE DATA DI NASCITA E SESSO-------------------*/
     for(i=0; i<4; i++)
          if(i==2 || i==3)
               printf("%c", anno[i]);
               
     printf("%c", charmese(mese));
     
     if(sesso=='M')
          printf("%02d", giorno);
     else
          printf("%d", giorno+40);
     
     /*-------------------PARTE COMUNE DI NASCITA-------------------*/
     //   NON HO LE COMPETENZE NECESSARIE
     
  printf("\n\n");
  system("PAUSE");	
  return 0;
}

int ctrl_consonante(char x)
{
     if(
     x =='B' ||
     x =='C' ||
     x =='D' ||
     x =='F' ||
     x =='G' ||
     x =='H' ||
     x =='J' ||
     x =='K' ||
     x =='L' ||
     x =='M' ||
     x =='N' ||
     x =='P' ||
     x =='Q' ||
     x =='R' ||
     x =='S' ||
     x =='T' ||
     x =='V' ||
     x =='W' ||
     x =='X' ||
     x =='Y' ||
     x =='Z' )
          return 1; //se consonante return 1
     else
          return 0; //se non è consonante return 0
}

int ctrl_vocale(char x)
{
     if(
     x =='A' ||
     x =='E' ||
     x =='I' ||
     x =='O' ||
     x =='U' )
          return 1; //se vocale return 1
     else
          return 0; //se non è vocale return 0
}

char charmese(int x)
{
     char res;
     
     switch(x)
     {
          case 1:
               res = 'A';
               break;
          case 2:
               res = 'B';
               break;
          case 3:
               res = 'C';
               break;
          case 4:
               res = 'D';
               break;
          case 5:
               res = 'E';
               break;
          case 6:
               res = 'H';
               break;
          case 7:
               res = 'L';
               break;
          case 8:
               res = 'M';
               break;
          case 9:
               res = 'P';
               break;
          case 10:
               res = 'R';
               break;
          case 11:
               res = 'S';
               break;
          case 12:
               res = 'T';
               break;
          default:
               printf("\nERROR: mese errato \n");
     }
               
     return res;
}
