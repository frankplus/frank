#include <stdio.h>

int main(int argc, char *argv[])
{
    int n, i;
    
    printf("Inserisci un numero da 1 a 1024: ");
    scanf("%d",&n);
    
    /*Controllo se valore non consentito*/
    if(n>1024) {
              printf("ERROR: numero maggiore di 1024 \n");
              system("pause");
              return 0;
              }
              
    printf("Il corrispettivo numero binario e': ");
       
    /*Conversione in binario*/  
    for(i=1024; i>=1; i=i/2) 
    {      
    if(n>=i) {
              printf("1");
              n = n-i;
              }
    else
        printf("0");
        
    }
    
    printf("\n");
    
    /*Conversione in binario con funzione printf*/
    printf("Conversione in binario con funzione printf \n");
    printf("COMING SOON \n");
  
  system("PAUSE");	
  return 0;
}
