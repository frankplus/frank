/*
  Name: Tris Esteso
  Author: Pham Francesco alias Pnb2frank
  Data pubblicazione: 16/04/12 21.15
  Description: Tris Esteso con dimensioni, segni di fila per vincere e profondità di esplorazione variabili.
*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <conio2.h>
#include <ctype.h>
#include <math.h>

int DIM; //dimensioni della griglia: 3x3 4x4 5x5.. massimo 10x10 (nel classico tris è 3)
int NWIN; //numero di segni di fila per vincere (nel classico tris è 3)

void griglia(); //funzione per visualizzare la griglia.
void leggimossa(char); //funzione per leggere mossa dell'utente.
int ctrlwin(char); //funzione per controllo se ci sono tris (nelle righe, colonne e diagolali.)

/*Funzioni per l'intelligenza artificiale*/
void move(int*, char);
int valutamossa(char, int*, int*, int, int);

char tris[10][10];

// INIZIO MAIN
int main(int argc, char *argv[])
{
      int i, j, rigioco, Nvuote;
      char simbolo, modalita, inizio;
      FILE *fp;
      
      repeat:
      
      // SCELTA DIMENSIONE E NWIN
      printf("BENVENUTO NEL TRIS!!! BY PHAM FRANCESCO \n\n");
      printf("Dimensione scacchiera (es.3=3x3, 4=4x4...): ");
      DIM = getche() - '0';
      printf("\nSegni di fila per fare Tris: ");
      NWIN = getche() - '0';
      
      printf("\n\n\nMODALITA' : \n\n");
      printf("1) 2 giocatori \n");
      printf("2) utente vs computer \n");
      printf("3) visualizza le ultime partite \n\n");
      printf("\t Scelta: ");
      modalita = getch();
      
      /*Inizializzazione della scacchiera*/
      for(i=0;i<DIM;i++)
            for(j=0;j<DIM;j++)
                  tris[i][j]=' ';
               
      // INIZIALIZZAZIONE Nvuote
      Nvuote=DIM*DIM;
      
      switch(modalita)
      {
            /*SE SI HA SCELTO 2 GIOCATORI*/
            case '1':
                  for(i=0;;++i) //ciclo apparentemente infinito ma viene chiuso dall'eventuale break
                  {
                        /*se nel ciclo i è pari tocca a X sennò tocca a O*/
                        if(i%2==0)
                              simbolo = 'X';
                        else
                              simbolo = 'O';
                        
                        system("cls"); //pulisce lo schermo
                        griglia();
                        leggimossa(simbolo);
                        Nvuote--;
                        
                        if(ctrlwin(simbolo))
                        {
                              system("cls"); //pulisce lo schermo
                              griglia();
                              printf("Il giocatore %c vince!! \n", simbolo);
                              break;
                        }
                        if(!Nvuote)
                        {
                              system("cls"); //pulisce lo schermo
                              griglia();
                              printf("Parita!! \n");
                              break;
                        }
                  }
                  
                  // SALVATAGGIO DELLA PARTITA
                  fp = fopen("partite.txt", "a");
                  fputc(DIM, fp);
                  for(i=0;i<DIM;i++)
                        for(j=0;j<DIM;j++)
                              fputc(tris[i][j], fp);
                  fputc('\n', fp);
                  fclose(fp);
                  
                  break;
                  
                  //FINE CASE 1
                  
            case '2': /*SE SI HA SCELTO UTENTE VS PC (CASE 2)*/  
                  
                  system("CLS");
                  printf("CHI GIOCA PER PRIMO? \n\n");
                  printf("1) Computer \n");
                  printf("2) Tu \n");
                  inizio = getch();
                  i=inizio;
                  
                  for(;;++i) //ciclo apparentemente infinito ma viene chiuso dall'eventuale break
                  {
                        /*se nel ciclo i è pari tocca a X sennò tocca a O*/
                        if(i%2==0)
                              simbolo = 'X';
                        else
                              simbolo = 'O';
                        
                        system("cls"); //pulisce lo schermo
                        griglia();
                        
                        // se giocatore == utente..
                        if(simbolo == 'X')
                              leggimossa(simbolo);
                        //altrimenti se giocatore == computer..
                        else if(simbolo == 'O')
                              move(&Nvuote, simbolo);
                        
                        Nvuote--;
                        
                        if(ctrlwin(simbolo))
                        {
                              system("cls"); //pulisce lo schermo
                              griglia();
                              if(simbolo == 'X')
                                    printf("Hai vinto!! \n");
                              else if(simbolo == 'O')
                                    printf("Il computer vince!!\n");
                              break;
                        }
                        if(!Nvuote)
                        {
                              system("cls"); //pulisce lo schermo
                              griglia();
                              printf("Parita!! \n");
                              break;
                        }
                  }
                  
                  // SALVATAGGIO DELLA PARTITA
                  fp = fopen("partite.txt", "a");
                  fputc(DIM, fp);
                  for(i=0;i<DIM;i++)
                        for(j=0;j<DIM;j++)
                              fputc(tris[i][j], fp);
                  fputc('\n', fp);
                  fclose(fp);
                  
                  break; 
                  
                  //FINE CASE 2
                
            case '3':
                  // CASE 3 (VISUALIZZAZIONE ULTIME PARTITE)
                  system("cls");
                  fp = fopen("partite.txt", "r");
                  if(fp == NULL)
                  {
                        printf("Non ci sono partite salvate!! \n");
                        break;
                  }
                  
                  do
                  {
                        DIM = fgetc(fp);
                        for(i=0;i<DIM;i++)
                              for(j=0;j<DIM;j++)
                                    tris[i][j] = fgetc(fp);
                        griglia();
                        putchar('\n');
                  }
                  while(fgetc(fp) != EOF);
                  
                  fclose(fp);
                  break;
                  
            default:
                  printf("ERROR: modalita' non valida \n");
      } 
      //FINE SWITCH
      
      system("PAUSE");       
      system("cls");
      
      do
      {
            printf("Premi INVIO per rigiocare. \n");
            printf("Premi ESC per chiudere \n");
            rigioco = getch();
            
            if(rigioco == 13)
            {
                  system("cls");
                  goto repeat;
            }
            if(rigioco == 27)
                  return 0;
      }
      while(rigioco != 13 && rigioco != 27);
      
      return 0;
} 
// FINE MAIN


/*___________________PARTE GRAFICA________________________*/
void griglia()
{
     int i,j;
     
     printf("\n  ");
     for(i=1;i<=DIM;i++)
          printf("  %d", i);
     putchar('\n');
     
     for(i=0;i<DIM;i++)
     {
          printf(" %c ", i+65);
          for(j=0;j<DIM;j++)
               printf("[%1c]",tris[i][j]);
          putchar('\n');
     }
}

/*___________________FUNZIONE CHE LEGGE LA MOSSA DELL'UTENTE________________________*/
void leggimossa(char wnr)
{
     /*
          Legge le mosse come coordinate es: a1, B2, c5.
          Funziona sia con le maiuscole che con le minuscole
          mossaX è orizzontale (numero)
          mossaY è verticale (lettera)
     */
     char mossaX, mossaY;
     
     do
     {
          printf("\nTocca a %c, inserisci la mossa: ", wnr);
          mossaY = toupper(getche()); //verticale quindi una lettera (toupper serve per convertirlo in maiuscola)
          mossaX = getche(); //orizzontale quindi numero
     }
     while(tris[mossaY-65][mossaX-49] != ' ' || mossaY-65>DIM || mossaX-49>DIM);
     
     tris[mossaY-65][mossaX-49] = wnr;
}

/*___________________FUNZIONE PER CONTROLLO SE CI SONO TRIS________________________*/
int ctrlwin(char wnr)
{
    register int count, i, j, x, y;
    
     /*Controllo righe e colonne*/
     for(i=0; i<DIM; i++)
     {
          /*righe*/
          count=0;
          for(j=0; j<DIM; j++)
               if(tris[i][j]==wnr)
               {
                    count++;
                    if(count==NWIN) return 1;
               }
               else
                    count=0;
          /*colonne*/       
          count=0;
          for(j=0; j<DIM; j++)
               if(tris[j][i]==wnr)
               {
                    count++;
                    if(count==NWIN) return 1;
               }
               else
                    count=0;
     }
     
     /*Controllo diagonali*/
     for(i=0; i<DIM; i++)
     {
          /*diagonale '\' parte basso-sinistra*/
          count=0;
          for(x=0,y=i ; (x>=0)&&(x<DIM)&&(y>=0)&&(y<DIM) ; x++,y++)
          {
               if(tris[y][x]==wnr)
               {
                    count++;
                    if(count==NWIN) return 1;
               }
               else
                    count=0;
          }
          
          /*diagonale '\' parte alto-destra*/
          count=0;
          for(x=i,y=0 ; (x>0)&&(x<DIM)&&(y>=0)&&(y<DIM) ; x++,y++)
          {
               if(tris[y][x]==wnr)
               {
                    count++;
                    if(count==NWIN) return 1;
               }
               else
                    count=0;
          }
          
          /*diagonale '/' parte alto-sinistra*/
          count=0;
          for(x=0,y=i ; (x>=0)&&(x<DIM)&&(y>=0)&&(y<DIM) ; x++,y--)
          {
               if(tris[y][x]==wnr)
               {
                    count++;
                    if(count==NWIN) return 1;
               }
               else
                    count=0;
          }
          
          /*diagonale '/' parte basso-destra.. NON FUNZIONA PERCHE'???*/
          count=0;
          for(x=i,y=9 ; (x>0)&&(x<DIM)&&(y>=0)&&(y<DIM) ; x++,y--)
          {
               if(tris[y][x]==wnr)
               {
                    count++;
                    if(count==NWIN) return 1;
               }
               else
                    count=0;
          }
     }
     
     return 0;
}

/*___________________FUNZIONI PER L'INTELLIGENZA ARTIFICIALE________________________*/
void move(int* Nvuote, char wnr)
{
     int meglioI, meglioJ, t, deep;
     
     deep = 19/sqrt(*Nvuote) +0.5; 
     /* istruzione per calcolare la profondità.. 
     costante / radice quadrata delle caselle vuote. 
     (+0.5 serve per arrotondare il risultato all'intero più vicino)*/
     
     printf("\nprofondita' = %d \n", deep);
     printf("caselle vuote = %d \n\n", *Nvuote);
     //system("PAUSE");
     
     printf("ATTENDERE...");
     t=valutamossa(wnr, &meglioI, &meglioJ, *Nvuote, deep);
     
     /*istruzioni di debug*/
     //printf("%d", deep);
     //printf("\n%d \n", t);
     //system("PAUSE");
     tris[meglioI][meglioJ] = wnr;
}
    
int valutamossa(char wnr, int *meglioI, int *meglioJ, int Nvuote, int deep)
{
     register int i, j, res=INT_MIN, tmp=INT_MIN;
     int DoveI, DoveJ;
     
     for(i=0; i<DIM; i++)
     {
          for(j=0; j<DIM; j++)
          {
               if(tris[i][j]==' ') 
               {
                    tris[i][j] = wnr;
                    if(ctrlwin(wnr)) 
                         tmp = Nvuote;
                    else if(Nvuote == 1 || deep==0)
                              tmp = 0;
                         else
                         {
                              if(wnr=='O')
                                   tmp = valutamossa('X', &DoveI, &DoveJ, Nvuote-1, deep-1);
                              else
                                   tmp = valutamossa('O', &DoveI, &DoveJ, Nvuote-1, deep-1);
                              tmp = -tmp;
                         }
                    if (tmp > res) 
                    {
                         res = tmp;
                         *meglioI = i;
                         *meglioJ = j;
                    }
                    tris[i][j]=' ';
               }
          }
     }
     return res;
}
