/*
    author: Pham Francesco
    Alias: frankplus
    Email: binh282828@hotmail.it
*/
#include "shooters.h"

using namespace std;

void PrintError(int num)
{
    char str[256];
    sprintf(str,"ERROR %d %s", num, SDL_GetError());
    MessageBox(NULL, str, "shooters error!", MB_OK);
    exit(num);
}
