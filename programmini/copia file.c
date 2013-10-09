#include <stdio.h>

int main(void)
{
     FILE *fporig, *fpres;
     
     fporig = fopen("abc.txt", "rb");
     fpres = fopen("copia.txt", "wb");
     
     if(fporig == NULL)
     {
          printf("ERROR");
          getchar();
          return 0;
     }
     
     while(!feof(fporig))
          fputc(fgetc(fporig), fpres);
     
     fclose(fporig);
     fclose(fpres);
     
     return 0;
}
