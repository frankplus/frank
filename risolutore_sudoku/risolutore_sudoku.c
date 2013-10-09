/*
    Name: Risolutore Sudoku
    Author: Pnb2Frank
    Date: 20.05.12 11:43
    
    Description: 
    
    Un risolutore del sudoku scritto in ANSI C per console.
    E' funzionante solo su windows perchè usa l'istruzione system("CLS"); e la funzione gotoxy per 
    muoversi nella console.
    per muoversi basta usare i tasti direzionali,
    per inserire un valore si usano i tasti numerici,
    per cancellare un valore premere zero, canc oppure backspace.
    è possibile caricare una griglia già compilata presente nel file save_sudoku.txt, basta premere F2.
    potete anche salvare una vostra griglia premendo F1 ma sovrascriverà quello precedente.
    La Funzione calcola() usa un algoritmo che risolve il sudoku cercando la cella con meno valori possibili, inserisce un valore e 
    fa una funzione ricorsiva.
    la funzione ricorsiva va in fondo, fino a quando una cella non ha più nessun valore possibile 
    oppure ha raggiunto la profondità massima cioè quando il sudoku è completo.
    By Pnb2Frank.
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

// DEFINISCO COSTANTI PER LE FRECCE DIREZIONALI
#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80

// PROTOTIPI DELLE FUNZIONI
void print(void);
void gotoxy(int x, int y);
void error(int x);
void pos_console(const int i, const int j, int* x, int* y);
int nvuote(void);
int calcola(void);
int valori_possibili(const int y, const int x, char valori[]);

/* 
    DICHIARO ARRAY GLOBALE SUDOKU CHE 
    HA NELLA 1° DIMENSIONE L'ASSE X
    NELLA 2° L'ASSE Y
*/
char sudoku[9][9];

// INIZIO FUNZIONE MAIN
int main(int argc, char *argv[])
{
    // DICHIARAZIONE VARIABILI
    unsigned int i, j, z, ind; //accumulatori
    unsigned int x, y;
    int tmp, input;
    char valori[10];
    FILE* filePointer;
    
    // INIZIALIZZAZIONE ARRAY
    for(i=0; i<9; i++)
        for(j=0; j<9; j++)
            sudoku[i][j] = ' ';
            
    // STAMPO IL SUDOKU VUOTO
    print();
    
    // RICHIEDO VALORI DA ASSEGNARE
    i = 0; j = 0; // inizializzo cursori che dicono quale cella stanno indicando
    for(;;)
    {
        // DEBUG
        gotoxy(0, 19);    
        printf("i=%d j=%d \n", i, j);
        printf("N. valori possibili: %d \n", valori_possibili(i, j, valori));
        printf("N. vuote: %d", nvuote());
        gotoxy(0, 15);
        for(tmp=0; tmp<50; tmp++) putchar(' ');
        gotoxy(0, 15);
        printf("Valori possibili: ");
        for(tmp=0; valori[tmp]; tmp++) printf("%d ", valori[tmp]);
        
        // MI POSIZIONO NELLA CELLA SEGNATA DA I E J
        pos_console(i, j, &x, &y); //trovo la posizione nella console della relativa cella
        gotoxy(x, y); // mi posiziono nella cella
        
        // RICEVO L'INPUT
        input = getch();
        
         // SE INVIO ESCO DAL CICLO FOR
        if(input == 13)
            break;
        
        // SE E' UN NUMERO DA 1 A 9 ASSEGNO VALORE ALLA CELLA
        else if(input >= '1' && input <= '9')
        {
            //CONTROLLO CHE IL NUMERO INSERITO E' TRA I VALORI POSSIBILI
            for(z=0; z<9; z++)
                if(valori[z] == input-'0')
                {
                    putchar(input); // lo mostro
                    sudoku[i][j] = input; // lo assegno all'array
                    // mi sposto nella prossima cella
                    if(j==8)
                    {
                        if(i < 8)
                        {
                            i++;
                            j = 0;
                        }
                    }
                    else
                        j++;
                        
                    break; //esco ciclo for
                }
        }
        
        // SE E' ZERO O BACKSPASE SVUOTA CELLA (per il tasto canc si va nell if successivo)
        else if(input == '0' || input == 8)
        {
            sudoku[i][j] = ' ';
            putchar(' ');
        }
        
        // TASTI DIREZIONALI E CANC (l'input vale 224 e il relativo codice del tasto premuto viene memorizzano in buffer)
        else if(input == 224)
        {
            input = getch(); // prende il codice numerico del tasto premuto memorizzato in buffer
            switch(input)
            {
                case UP:
                    if(i > 0)
                        i--;
                    break;
                case LEFT:
                    if(j > 0)
                        j--;
                    break;
                case RIGHT:
                    if(j < 8)
                        j++;
                    break;
                case DOWN:
                    if(i < 8)
                        i++;
                    break;
                case 83: // SE E' CANC SVUOLA CELLA.
                    sudoku[i][j] = ' ';
                    putchar(' ');
                    break;
                //default:
                    //error(1);
            }
        }
        else if(input == 0) //SE E' TRA I TASTI FUNZIONE (F1 E F2)
        {
            switch(getch())
            {
                case 59: // F1
                    filePointer = fopen("save_sudoku.txt", "w"); // APRI FILE COME SCRITTURA
                    for(z=0; z<9; z++)
                        for(ind=0; ind<9; ind++)
                            fputc(sudoku[z][ind], filePointer); // PER OGNI CELLA INSERISCI IL VALORE NEL FILE
                    fclose(filePointer); // CHIUDI FILE
                    gotoxy(0, 13);
                    printf("SALVATO CON SUCCESSO"); // COMUNICA LA RIUSCIRA
                    Sleep(800); // ATTENDI PER UN MOMENTO
                    gotoxy(0, 13); // ELIMINA LA STRINGA SULLA CONSOLE
                    for(z=0; z<50; z++)
                        putchar(' ');
                    break;
                case 60: // F2
                    filePointer = fopen("save_sudoku.txt", "r"); // APRI FILE COME LETTURA
                    
                    if(!filePointer) // SE IL FILE NON E' PRESENTE
                    {
                        gotoxy(0, 13);
                        printf("IL FILE NON E' PRESENTE"); // COMUNICA LA NON RIUSCITA
                        Sleep(800); // ATTENDI PER UN MOMENTO 
                        gotoxy(0, 13); // ELIMINA LA STRINGA SULLA CONSOLE
                        for(z=0; z<50; z++)
                            putchar(' ');
                    }
                    else // SE IL FILE E' PRESENTE
                    {
                        for(z=0; z<9; z++)
                            for(ind=0; ind<9; ind++)
                                sudoku[z][ind] = fgetc(filePointer);// PER OGNI CELLA INSERISCI IL VALORE NELL'ARRAY
                        fclose(filePointer); // CHIUDI FILE
                        system("CLS"); //PULISCI SCHERMO
                        print(); // STAMPA SUDOKU
                        gotoxy(0, 13);
                        printf("CARICATO CON SUCCESSO"); // COMUNICA RIUSCITA
                        Sleep(800); // ATTENDI PER UN MOMENTO
                        gotoxy(0, 13); // ELIMINA LA STRINGA SULLA CONSOLE
                        for(z=0; z<50; z++)
                            putchar(' ');
                    }
                    break;
            }
        }
        else // SE IL TASTO PREMUTO NON E' ESATTO, COMUNICA ERRORE 2
            //error(2); lascio come commento così se l'utente preme per errore un tasto sbagliato, il programma non esce.
            
        // SE IL SUDOKU E' PIENO ESCE
        if(!nvuote())
            break;
    }
    
    // PULISCI LO SCHERMO
    system("CLS");
    
    // SE LE CASELLE RIEMPITE SONO MENO DI 20 ERRORE (NON PUO' CALCOLARE SOLUZIONE)
    if(nvuote() > 81-20)
    {
        gotoxy(0, 13);
        printf("Questo sudoku non e' valido \nLe celle compilate sono meno di 20, \npuo' darsi che questa soluzione non sia l'unica..");
        //error(3);
    }
    
    // CALCOLA E MOSTRA SUDOKU COMPLETATO (se la funzione calcola() ritorna 0 il sudoku non ha soluzione)
    if(!calcola()) error(4);
    gotoxy(0,0);
    print();
    
    // ESCE
    gotoxy(0, 15);
    printf("\n\nPremi un tasto per chiudere ...");
    getch();	
    return 0;
}
// FINE FUNZIONE MAIN

void print()
{
    unsigned int i, j;
    
    // STAMPO IL VALORE PER OGNI CELLA
    for(i=0; i<9; i++)
    {
        if((i % 3) == 0 && i>0) // SE SI TROVA AL PUNTO DI DIVISIONE SOTTO-GRIGLIA
            putchar('\n'); // VAI A CAPO
            
        for(j=0; j<9; j++)
        {
            if((j % 3) == 0 && j>0) // SE SI TROVA AL PUNTO DI DIVISIONE SOTTO-GRIGLIA
                putchar(' '); // METTI UNA SPAZIO
            printf("[%c]", sudoku[i][j]); // INSERISCI CELLA
        }
        putchar('\n'); // FINE RIGA, VAI A CAPO RIGA
    }
    
    // STAMPO LA LEGENDA SULLA DESTRA DELLA CONSOLE
    gotoxy(35, 2); printf("Guida:");
    gotoxy(35, 3); printf("F1 per salvare una griglia");
    gotoxy(35, 4); printf("F2 per caricare una griglia");
    gotoxy(35, 5); printf("Tasti direzionali per muoverti");
    gotoxy(35, 6); printf("Tasti numerici per inserire valore");
    gotoxy(35, 7); printf("zero, backspace, canc per cancellare cella");
    gotoxy(35, 8); printf("INVIO per avviare la risoluzione");
    gotoxy(35, 10); printf("Crediti: Pnb2Frank");
}

// FUNZIONE GOTOXY FUZIONANTE SOLO SU WINDOWS (non scritto da me)
void gotoxy(int x, int y)
{
    COORD ord;
    ord.X = x;
    ord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ord);
}

// FUNZIONE CHE MOSTRA L'ERRORE ED ESCE
void error(int x)
{
    system("CLS");
    printf("ERROR = %d \n\n", x);
    switch(x)
    {
        case 1:
            printf("Input = 224 ma non e' un tasto direzionale valido.");
            break;
        case 2:
            printf("Il tasto premuto non e' valido.");
            break;
        case 3:
            printf("Le celle completate non sono sufficenti, \nper trovare la soluzione servono 20 celle completate.");
            break;
        case 4:
            printf("I valori inseriti non sono esatti, non c'è una soluzione a questo sudoku.");
            break;
    }
    printf("\n\nPress any key to continue ...");
    getch();	
    exit(-1);
}

// FUNZIONE CHE DATA LA CELLA INDICA LA SUA POSIZIONE NELLA CONSOLE PER LA FUNZIONE GOTOXY
void pos_console(const int i, const int j, int *x, int *y)
{
    switch(i)
    {
        case 0:
            *y = 0;
            break;
        case 1:
            *y = 1;
            break;
        case 2:
            *y = 2;
            break;
        case 3:
            *y = 4;
            break;
        case 4:
            *y = 5;
            break;
        case 5:
            *y = 6;
            break;
        case 6:
            *y = 8;
            break;
        case 7:
            *y = 9;
            break;
        case 8:
            *y = 10;
            break; 
    }
    switch(j)
    {
        case 0:
            *x = 1;
            break;
        case 1:
            *x = 4;
            break;
        case 2:
            *x = 7;
            break;
        case 3:
            *x = 11;
            break;
        case 4:
            *x = 14;
            break;
        case 5:
            *x = 17;
            break;
        case 6:
            *x = 21;
            break;
        case 7:
            *x = 24;
            break;
        case 8:
            *x = 27;
            break; 
    }
}

// FUNZIONE CHE RICAVA IL NUMERO DI CELLE VUOTE PARTENDO DA 81 E DECREMENTANDO LE CELLE COMPILATE
int nvuote(void)
{
    int count=81;
    char i, j;
    for(i=0; i<9; i++)
        for(j=0; j<9; j++)
            if(sudoku[i][j] != ' ')
                count--;
    return count;
}

// FUNZIONE PRINCIPALE CHE RISOLVE IL SUDOKU
int calcola(void)
{
    if(!nvuote()) return 1; // SE E' STATO RAGGIUNTO PROFONDITA' MASSIMA (SUDOKU COMPLETATO) RITORNA 1
    
    // DICHIARAZIONE
    char valori[10]; // CREA ARRAY CON I VALORI POSSIBILI
    register char i, j;
    char posx, posy, temp, nvalori=9;
    
    // TROVA LA CELLA VUOTA CON IL MINOR NUMERO DI VALORI POSSIBILI
    for(i=0; i<9; i++)
        for(j=0; j<9; j++)
            if((sudoku[i][j] == ' ') && ((temp=valori_possibili(i,j,valori)) < nvalori))
            {
                nvalori = temp;
                posx = j;
                posy = i;
            }
    
    // BRUTE-FORCE PROVA PER OGNI CELLA TUTTI I VALORI CHE POSSONO ASSUMERE
    valori_possibili(posy, posx, valori); //cerca i valori che può assumere la cella con minor candidati
    for(i=0; valori[i]; i++) // per ogni valore che può assumere
    {
        sudoku[posy][posx] = valori[i]+'0'; // lo inserisce nell'array sudoku
        if(calcola()) 
            return 1; // se la funzione ricorsiva di questa funzione ritorna 1(raggiunto profondita' massima), ritorna 1
        else
            sudoku[posy][posx] = ' '; // se valore non esatto (la funzione ricorsiva ha ritornato 0), lo toglie dalla cella e ne inserisce un'altro
    }
    return 0; // se sono finiti i valori possibili per la cella, ritorna 0
}

int valori_possibili(const int y, const int x, char valori[])
{
    char i, j, count, posx, posy;
    
    // INIZIALIZZAZIONE ARRAY VALORI CON I NUMERI DA 1 A 9
    for(i=0; i<9; i++)
        valori[i] = i+1;
    valori[9] = '\0';
    
    // CONTROLLO RIGA
    for(i=0; i<9; i++)// per ogni cella compilata della riga
        if(sudoku[y][i] != ' ')
            for(j=0; j<9; j++)// cerca il valore nell'array valori[]
                if(valori[j] == (sudoku[y][i]-'0'))
                {
                    for(;;) // e lo elimina slittando l'array
                    {
                        valori[j] = valori[j+1];
                        if(!valori[j]) // fino a quando non si raggiunge fine stringa
                            break;
                        else
                            j++;
                    }
                    break;
                }
    
    // CONTROLLO COLONNA
    for(i=0; i<9; i++)// per ogni cella compilata della colonna
        if(sudoku[i][x] != ' ')
            for(j=0; j<9; j++)// cerca il valore nell'array valori[]
                if(valori[j] == (sudoku[i][x]-'0'))
                {
                    for(;;)// e lo elimina slittando l'array
                    {
                        valori[j] = valori[j+1];
                        if(!valori[j]) // fino a quando non si raggiunge fine stringa
                            break;
                        else
                            j++;
                    }
                    break;
                }
    
    // CONTROLLO SOTTO-GRIGLIA 3X3
    
    // inizializzo posy con l'inizio della sotto-griglia 3x3 
    //es. se si trova nella pos. 5 va nella pos. 2(pos.0 è il margine superiore, stessa cosa per posx).
    posy = y/3*3;
    for(i=0; i<3; i++, posy++)
    {
        posx = x/3*3;
        for(j=0; j<3; j++, posx++)
            if(sudoku[posy][posx] != ' ')// se la cella è compilata
                for(count=0; count<9; count++)// cerca il valore nell'array valori[]
                    if(valori[count] == (sudoku[posy][posx]-'0'))
                    {
                        for(;;)// e lo elimina slittando l'array
                        {
                            valori[count] = valori[count+1];
                            if(!valori[count]) // fino a quando non si raggiunge fine stringa
                                break;
                            else
                                count++;
                        }
                        break;
                    }
    }
    
    // RITORNA IL NUMERO DI VALORI POSSBILILI (i valori sono messi nell'array valori[] )
    return strlen(valori);
}
