#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>

void gotoxy(int x, int y);
void error(int);
long int lenFile(FILE*);

int main(void)
{
     register int i, j, count;
     int nPart, point;
     char c;
     long int lengthFile, div, div_exe, pos;
     char nomeFilePart[100] = "temp.partN";
     char nomeFileOrig[100] = "La guida completa C++ .pdf";
     char nomeFileOut[100];
     FILE *fporig, *fpres, *fpbat;
     
     printf("1) Dividi file \n");
     printf("2) Unisci file \n\n");
     printf("\t Scelta: ");
     switch(getch())
     {
          case '1':
               system("CLS");
               
               // RICHIEDO PERCORSO DEL FILE
               printf("Inserisci percorso del file: ");
               gets(nomeFileOrig);
               
               // RICHIEDO IN QUANTE PARTI DIVIDO
               printf("n. parti: ");
               scanf("%d", &nPart);
               
               system("CLS");
               
               // APRO FILE
               fporig = fopen(nomeFileOrig, "rb");
               if(!fporig)
                    error(3);
               
               // RICAVO LA LUNGHEZZA DEL FILE ORIGINE  
               lengthFile = lenFile(fporig);
               fseek(fporig, 0, 0);

               // DIVIDO IL FILE IN NPARTI E TROVO QUANTI BYTE SARA' OGNI PARTE
               div = lengthFile/nPart + 1;
               
               // DIVIDO LA LUNGHEZZA IN 50 PER TROVARE IL MOMENTO NEL QUALE INCREMENTARE LO STATO DI ESECUZIONE
               div_exe = lengthFile/50 +1;
               
               printf("\nStato Operazione:");
               gotoxy(49, 5);
               printf("FINE");
               gotoxy(0, 5);
               
               // MI RIPOSIZIONO A INIZIO FILE PER COMINCIARE LA COPIA
               for(i=1, count=1; i<=nPart; i++)
               {
                    sprintf(nomeFilePart, "%s.part%d", nomeFileOrig, i);
                    fpres = fopen(nomeFilePart, "wb");
                    for(pos=0; ((c=fgetc(fporig))!=EOF || !feof(fporig)) && pos<div; pos++, count++)
                    {
                         fputc(c, fpres);
                         
                         // VISUALIZZO STATO DELL'ESECUZIONE
                         if(count == div_exe)
                         {
                              count = 1;
                              putchar('\333');
                         }
                    }
               }
               
               // CHIUDO I FILE
               fclose(fporig);
               fclose(fpres);
               
               // CREO FILE BAT
               sprintf(nomeFileOut, nomeFileOrig);
               strcat(nomeFileOut, ".bat");
               fpbat = fopen(nomeFileOut, "w");
               // INIZIO SCRITTURA
               fprintf(fpbat, "echo off\n");
               fprintf(fpbat, "cls\n");
               fprintf(fpbat, "copy /b ");
               for(i=1; i<=nPart; i++)
               {
                    if(i>1)
                         fprintf(fpbat, " + ");
                    sprintf(nomeFilePart, "%s.part%d", nomeFileOrig, i);
                    fprintf(fpbat, "\"%s\"", nomeFilePart);
               }
               fprintf(fpbat, " \"(1)%s\"", nomeFileOrig); 
               fputc('\n', fpbat);
               fprintf(fpbat, "echo Completed\n");
               fprintf(fpbat, "pause\n");
               
               // CHIUDO FILE BAT
               fclose(fpbat);
               
               // ESCO
               putchar('\n');
               printf("Premere un tasto per continuare ...");
               getch();
               
               break;
               // FINE CASE 1
          case '2':
               // CASE 2: UNISCO I FILE
               
               system("CLS");
               
               // RICHIEDO IN QUANTE PARTI DIVIDO
               printf("Inserisci percorso del file: ");
               gets(nomeFilePart);
               
               system("CLS");
               
               printf("\nStato Operazione:");
               
               // RICAVO IL NOME DEL FILE ORIGINALE DAL NOME DEL FILE PARTIZIONATO
               for(j=0; nomeFilePart[j]; j++)
                    if(nomeFilePart[j] == '.')
                         point = j;
               for(j=0; j<point; j++)
                    nomeFileOrig[j] = nomeFilePart[j];
               nomeFileOrig[point] = '\0';
               
               // NOMINO IL FILE RISULTANTE CON (1) + NOMEFILEORIG
               sprintf(nomeFileOut, "(1)");
               strcat(nomeFileOut, nomeFileOrig);
               
               //APRO FILE RISULTANTE
               fpres = fopen(nomeFileOut, "wb");
               
               // UNISCO I FILE
               for(i=1, count=1; ;i++)
               {
                    // APRO FILE PARTIZIONATO 
                    // MI METTO A FINE STRINGA PER MODIFICARE IL NUMERO DELLA PARTIZIONE
                    for(j=0; nomeFilePart[j+1]; j++);
                    sprintf(&nomeFilePart[j], "%d", i);
                    fporig = fopen(nomeFilePart, "rb");
                    if(!fporig)
                    {
                         if(i == 1)
                              error(2);
                         else
                              break;
                    }
                         
                    // RICAVO LA LUNGHEZZA DEL FILE ORIGINE
                    lengthFile = lenFile(fporig);
                    fseek(fporig, 0, 0);
                    // DIVIDO LA LUNGHEZZA IN 50 PER TROVARE IL MOMENTO NEL QUALE INCREMENTARE LO STATO DI ESECUZIONE
                    div_exe = lengthFile/50;
                    
                    // VISUALIZZO PARTE IN CARICAMENTO
                    gotoxy(49, 5);
                    printf("Parte %d", i);
                    gotoxy(0, 5);
                    
                    // COPIO IL FILE .PART NEL FILE RISULTANTE
                    while((c=fgetc(fporig))!=EOF  || !feof(fporig))
                    {
                         fputc(c, fpres);
                              
                         // VISUALIZZO STATO DELL'ESECUZIONE
                         if(count == div_exe)
                         {
                              count = 1;
                              putchar('\333');
                         }
                         count++;
                    }
                    // CANCELLO STATO DI ESECUZIONE PER COMINCIARE CON FILE SUCCESSIVO
                    gotoxy(1, 5);
                    for(j=1; j<=51; j++)
                         putch(' ');
               }
               break;
          default:
               error(1);
     }
               
     return 0;
}

void error(int n)
{
     system("CLS");
     printf("ERRORE!!!!!! \nCODICE = %d \n", n);
     switch(n)
     {
          case 1:
               printf("Modalita' non conpresa \n\n");
               break;
          case 2:
               printf("File inesistente \n\n");
               break;
          case 3:
               printf("File inesistente \n\n");
               break;
     }
     printf("Premere un tasto per continuare ...");
     getch();
     exit(-1);
}

long int lenFile(FILE * fp)
{
     // MI POSIZIONO A FINE FILE PER TROVARE LUNGHEZZA FILE
     fseek(fp, 0, 2);
     return ftell(fp);
}

// FUNZIONE GOTOXY FUZIONANTE SOLO SU WINDOWS
void gotoxy(int x, int y)
{
    COORD ord;
    ord.X = x;
    ord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ord);
}
