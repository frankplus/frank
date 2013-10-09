/*
  Name: Tris o Tic-Tac-Toe
  Copyright: Pham Francesco
  Author: Pham Francesco
  Date: 25/03/12 18.59
  Description: Gioco del Tris con algoritmo Minimax per l'intelligenza del pc
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <conio.h>

void griglia(); //funzione per visualizzare la griglia.
void leggimossa(char wnr); //funzione per leggere mossa dell'utente.
int ctrlwin(char wnr); //funzione per controllo se ci sono tris (nelle righe, colonne e diagolali.)
int endgame(); //funzione per controllo se le caselle sono tutte occupate

/*Funzioni per l'intelligenza artificiale*/
int nvuote(void);
void move(void);
int valutamossa(char wnr, int deep);

char casella[10]; //dichiarazione del vettore delle caselle


int main(int argc, char *argv[])
{
    int i, modalita, rigioco, giocatore; //giocatore 1 = utente, giocatore 0 = computer.
    char simbolo;
    
    repeat:

    printf("BENVENUTO NEL TRIS!!! BY PHAM FRANCESCO \n\n");
    printf("1) 2 giocatori \n");
    printf("2) utente vs computer \n\n");
    printf("\t Scelta: ");
    scanf("%d", &modalita);
    
    /*inizializzazione della griglia*/
    for(i=1; i<=9; ++i)
        casella[i]=' ';
    
    switch(modalita)
    {
        /*SE SI HA SCELTO 2 GIOCATORI*/
        case 1:
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
                    if(ctrlwin(simbolo))
                    {
                        system("cls"); //pulisce lo schermo
                        griglia();
                        printf("Il giocatore %c vince!! \n", simbolo);
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
                break; //uscita switch (fine case 1)
                
        /*SE SI HA SCELTO UTENTE VS PC*/  
        case 2:
                for(i=0;;++i) //ciclo apparentemente infinito ma viene chiuso dall'eventuale break
                {
                    /*se nel ciclo i è pari tocca a X sennò tocca a O*/
                    if(i%2==0)
                    {
                        giocatore = 1;
                        simbolo = 'X';
                    }
                    else
                    {
                        giocatore = 0;
                        simbolo = 'O';
                    }
                        
                    system("cls"); //pulisce lo schermo
                    griglia();
                    
                    // se giocatore == utente..
                    if(giocatore==1)
                        leggimossa(simbolo);
                    //altrimenti se giocatore == computer..
                    else if(giocatore==0)
                        move();
                        
                    if(ctrlwin(simbolo))
                    {
                        system("cls"); //pulisce lo schermo
                        griglia();
                        if(giocatore==1)
                            printf("Hai vinto!! \n");
                        else if(giocatore==0)
                            printf("Il computer vince!!\n");
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
                break; //uscita switch (fine case 2)
        
        default:
                printf("ERROR: modalita' non valida \n");
    }
    
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
        else if(casella[mossa]!=' ') //controlla se casella è già occupata
                printf("ERROR: casella gia' occupata \n");
    }
    while(mossa<1 || mossa>9 || casella[mossa]!=' ');
    
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


/*FUNZIONI PER L'INTELLIGENZA ARTIFICIALE*/

int nvuote(void)
{
    int i,vuote=0;
    for(i=1;i<=9;i++)
        if(casella[i]==' ') vuote++;
    return vuote;
}
    
void move(void)
{
    int i;
    int max=INT_MIN, mi=1, t; //t indica l'efficacia della mossa
    for(i=1; i<=9; i++)
        if(casella[i]==' ')
        {
            casella[i]='O';
            t=valutamossa('X', 20);
            //printf("casella[%d] efficacia = %d\n",i, t); //NON UTILE PER L'UTENTE
            if(t>max)
            {
                max=t;
                mi=i; //cerca la casella migliore e la assegna a mi
            }
            casella[i]=' ';
        }
           
    casella[mi]='O';
}
 
int valutamossa(char wnr, int deep)//Minimax
{
        if(ctrlwin('O'))
                return INT_MAX;
        if(endgame())
                return 0;
        int i, res, tmp;
        
        if(wnr=='X')
        {
                res=1;
                for(i=1;i<=9;i++)
                    {
                            if(casella[i]==' ')
                            {
                                    casella[i]='X';
                                    if(ctrlwin('X'))
                                            if(deep==20)
                                            {
                                                    casella[i]=' ';
                                                    return INT_MIN;
                                            }
                                            else
                                                    res-=2;
                                    else if((tmp=valutamossa('O', deep - 1))<res)
                                            res=tmp;
                                    casella[i]=' ';
                            }
                    }
        }
        else
        {
                res=-1;
                for(i=1;i<=9;i++)
                        {
                                if(casella[i]==' ')
                                {
                                        casella[i]='O';
                                        if(ctrlwin('O'))
                                                res+=2;
                                        else if((tmp=valutamossa('X', deep - 1))>res)
                                                res=tmp;
                                        casella[i]=' ';
                                }
                        }
        }
        return res;
}
