#include <stdio.h>
#include <stdlib.h>
#include <limits.h> //per INT_MIN e INT_MAX

void esercizio1()
{
    /*Predisporre un programma, che determini il maggiore, 
    il minore e la media degli n valori immessi dall’utente.*/
    printf("ESERCIZIO 1\n\n");
    printf("Questo programma determina il maggiore, \nil minore e la media degli n valori immessi dall utente.\n\n");
    
    int max, min, totale, n, i;
    max=INT_MIN;
    min=INT_MAX;
    totale=0;
    n=1;
    
    printf("pre max=%d \npre min=%d \n\n", max, min);
    
    i=0; //inizializzazione del contatore
    while(1==1) //ciclo apparentemente infinito ma c'è il break
    {
        printf("Inserire un numero (0 per terminare): ");
        scanf("%d", &n);
        if(n==0) //break se è stato inserito 0
            break;
        if(n>max)
            max=n;
        if(n<min)
            min=n;
        totale += n;
        i++; //incremento contatore
    }
        
    printf("Il massimo e': %d \n", max);
    printf("Il minimo e': %d \n", min);
    printf("Il totale e': %d \n", totale);
    printf("La media e': %d \n", totale/i);
}

void esercizio2()
{
    /*Predisporre un programma che stampi un rettangolo permettendo 
    all’utente di decidere i caratteri che devono comporre 
    la cornice e la parte interna del rettangolo e quante volte 
    debba essere ripetuta la visualizzazione del rettangolo. 
    Il numero di linee e di colonne del rettangolo viene deciso 
    a tempo di esecuzione dall’utente;*/
    
    printf("ESERCIZIO 2\n\n");
    
    int nrig, ncol, irig, icol;
    char cornice, interno;
    
    printf("Inserisci il numero di righe: ");
    scanf("%d", &nrig);
    
    printf("Inserisci il numero di colonne: ");
    scanf("%d", &ncol);
    
    printf("scegli la cornice: ");
    scanf(" %c", &cornice);
    
    printf("scegli l'interno: ");
    scanf(" %c", &interno);
    
    for(irig=1; irig<=nrig; ++irig)
    {
        for(icol=1; icol<=ncol; ++icol)
        {
            if(icol==1 || icol==ncol || irig==1 || irig==nrig)
                printf("%c", cornice);
            else
                printf("%c", interno);
        }
        printf("\n");
    }
    
}

void esercizio3()
{
    /*Realizzare un programma che richieda all’utente n interi, 
    e visualizzi il numero di volte in cui sono stati eventualmente 
    immessi i valori 10, 100 e 1000.*/
    printf("ESERCIZIO 3\n\n");
    printf("Questo programma conta quante volte si digita 10/100/1000 \n\n");
    int n, nvolte;
    
    n=0;
    nvolte=0;
    
    do
    {
        printf("inserisci numero (0 per terminare): ");
        scanf("%d", &n);
        if(n==10 || n==100 || n==1000)
            ++nvolte;
    }
    while(n!=0);
    
    printf("\nHai digitato 10/100/1000 %d volte", nvolte);
}

void esercizio4()
{
    /*Predisporre un programma che visualizzi la 
    tavola pitagorica del sistema di numerazione decimale.*/
    printf("ESERCIZIO 4\n\n");
    
    int irig, icol;
    for(irig=1; irig<=10; ++irig)
    {
        for(icol=1; icol<=10; ++icol)
            printf(" %-3d", irig*icol); //utilizzo %-3d per allineare i numeri
        
        printf("\n");
    }
}

void esercizio5()
{
    printf("ESERCIZIO 5\n\n");
    
    float a, b, c, d;
    a = 123.456;
    b = 2700000;
    c = 0.99999999;
    d = 0.07;
    printf("%e \n", a);
    printf("%e \n", b);
    printf("%e \n", c);
    printf("%e \n", d);
}


int main(int argc, char *argv[])
{
    /*esercizio2();
    printf("\n\n");*/
    
    esercizio1();
    printf("\n\n");
    
    esercizio2();
    printf("\n\n");
    
    esercizio3();
    printf("\n\n");
    
    esercizio4();
    printf("\n\n");
    
    esercizio5();
    printf("\n\n");
    
    
    system("PAUSE");	
    return 0;
}

