#include "ClassSDL.h"

using namespace std;

//The attributes of the screen
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

ClassSDL::ClassSDL()
{
    screen = smiley = NULL;
    SDL_Init( SDL_INIT_EVERYTHING );
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
    SDL_WM_SetCaption("Smiley", NULL);
    background = SDL_LoadBMP( "background.bmp" );
}

ClassSDL::~ClassSDL()
{
    SDL_FreeSurface(smiley);
    SDL_FreeSurface(screen);
    SDL_Quit();
}

void ClassSDL::ApplySmiley(char* FileName)
{
    smiley = SDL_LoadBMP(FileName);
    apply_surface( 0, 0, background, screen );
    int x = (SCREEN_WIDTH-smiley->w)/2;
    int y = (SCREEN_HEIGHT-smiley->h)/2;
    apply_surface(x, y, smiley, screen);
    SDL_Flip( screen );
}

void ClassSDL::apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface( source, NULL, destination, &offset );
}
