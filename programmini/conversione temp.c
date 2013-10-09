#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int main()
{
    short termina = 0;
    char scelta;
    float celsius, fahr;
    
    while(termina == 0)
    {
        printf("1) Conversione Celsius - Fahrenheit \n");
        printf("2) Conversione Fahrenheit - Celsius \n");
        printf("3) Terminare \n\n");
        printf("Scelta? ");

        scelta=getch();
        printf("\n");
        
        switch(scelta)
        {
            case '1':
                printf("Inserisci valore in Celsius: ");
                scanf("%f", &celsius);
                printf("Il valore in Fahrenheit e': %.2f \n", celsius*1.8+32);
                break;
            case '2':
                printf("Inserisci valore in Fahrenheit: ");
                scanf("%f", &fahr);
                printf("Il valore in Celsius e': %.2f \n", (fahr-32)/1.8);
                break;
            case '3':
                termina = 1;
                break;
            default:
                printf("Mi stai prendendo in giro? Scelta non disponibile.. \n");
        }
        printf("__________________________________________________________________________\n");
    }
    
    printf("CIAO CIAO COGLIONE! \n"); 
    system("PAUSE");
}
