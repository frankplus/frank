/*
  Name: Tris o Tic-Tac-Toe
  Copyright: 
  Author: Pham Francesco
  Date: 25/03/12 18.59
  Description: 
*/

#include <stdio.h>
#include <stdlib.h>

void griglia(); //funzione per visualizzare la griglia.
void leggimossa(char wnr); //funzione per leggere mossa dell'utente.
int ctrlwin(char wnr); //funzione per controllo se ci sono tris (nelle righe, colonne e diagolali.)
int endgame(); //funzione per controllo se le caselle sono tutte occupate

char casella[10]; //dichiarazione del vettore delle caselle


int main(int argc, char *argv[])
{
    int i, player;
    char start;
    
    printf("BENVENUTO NEL TRIS!!! BY PHAM FRANCESCO \n\n");
    printf("In questa versione di tris e' possibile giocare solamente tra 2 utenti.. \n");
    printf("nella prossima versione sara' implementato l'intelligenza artificiale \n");
    printf("e potrete giocare contro il computer!! \n\n");
    printf("Premi invio per cominciare a giocare!!");
    
    /*attende il tasto invio*/
    do
        start=getchar();
    while(start != '\n');
    
    /*inizializzazione della griglia*/
    for(i=1; i<=9; ++i)
        casella[i]=' ';
    
    for(i=0;;++i) //ciclo apparentemente infinito ma viene chiuso dall'eventuale break
    {
        /*se nel ciclo i è pari tocca a X sennò tocca a O*/
        if(i%2==0)
            player = 'X';
        else
            player = 'O';
            
        system("cls"); //pulisce lo schermo
        griglia();
        leggimossa(player); 
        if(ctrlwin(player))
        {
            system("cls"); //pulisce lo schermo
            griglia();
            printf("Il giocatore %c vince!! \n", player);
            break;
        }
        if(endgame())
        {
            system("cls"); //pulisce lo schermo
            griglia();
            printf("Parita!! \n");
            break;
        }
    }
    
    printf("\n");
    system("PAUSE");	
    return 0;
}



void griglia()
{
    printf("per indicare la mossa usa il tastierino numerico (1-9) \n\n");
    
    printf("+---------+---------+---------+ \n");
    printf("|         |         |         | \n");
    printf("|    %c    |    %c    |    %c    | \n", casella[7], casella[8], casella[9]);
    printf("|7        |8        |9        | \n");
    printf("+---------+---------+---------+ \n");
    printf("|         |         |         | \n");
    printf("|    %c    |    %c    |    %c    | \n", casella[4], casella[5], casella[6]);
    printf("|4        |5        |6        | \n");
    printf("+---------+---------+---------+ \n");
    printf("|         |         |         | \n");
    printf("|    %c    |    %c    |    %c    | \n", casella[1], casella[2], casella[3]);
    printf("|1        |2        |3        | \n");
    printf("+---------+---------+---------+ \n\n\n");
}


void leggimossa(char wnr)
{
    int mossa;
    
    do
    {
        printf("\nTocca a %c, inserisci la mossa : ", wnr);
        scanf("%d", &mossa);
        
        if(mossa<1 || mossa>9)
            printf("ERROR: mossa non valida \n");
    }
    while(mossa<1 || mossa>9);
    
    casella[mossa] = wnr;
}

int ctrlwin(char wnr)
{
    if( (casella[1]==wnr && casella[2]==wnr && casella[3]==wnr) || // 1° riga
        (casella[4]==wnr && casella[5]==wnr && casella[6]==wnr) || // 2° riga
        (casella[7]==wnr && casella[8]==wnr && casella[9]==wnr) || // 3° riga
        (casella[1]==wnr && casella[4]==wnr && casella[7]==wnr) || // 1° colonna
        (casella[2]==wnr && casella[5]==wnr && casella[8]==wnr) || // 2° colonna
        (casella[3]==wnr && casella[6]==wnr && casella[9]==wnr) || // 3° colonna
        (casella[1]==wnr && casella[5]==wnr && casella[9]==wnr) || // diagonale "/"
        (casella[7]==wnr && casella[5]==wnr && casella[3]==wnr)    // diagonale "\"
       ) return 1;
    else
        return 0;
}


int endgame()
{
    int i;
    
    for(i=1; i<=9; ++i) 
    {
        if(casella[i] == ' ')
            return 0;
    }
    return 1;
}
