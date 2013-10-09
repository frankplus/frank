//Main.cpp

#include <SDL/SDL.h>
#include <iostream>
#include "Ball.h"
#include <vector>
using namespace std;

//Surfaces
SDL_Surface *screen = NULL;
SDL_Surface *background = NULL;
SDL_Surface *ball = NULL;

SDL_Event evento, testEvento;
Uint8 *keys;

//Variabili
const int xDialog = 600;
const int yDialog = 500;
const int bpp = 32;
const int frameSkip = 30;
const int makeBallDelay = 50;
int objects = 0;
int newobj = 0;
int direction;
int speed;
//Funzioni
void makeBackground ( void );
void freeSurfaces ( void );

//Definizione delle funzioni
void makeBackground ( void )
{
	SDL_BlitSurface ( background, NULL, screen, NULL );
}

void freeSurfaces ( void )
{
	SDL_FreeSurface ( background );
	SDL_FreeSurface ( ball );
}


int main ( int argc, char *argv[] )
{

	if ( SDL_Init ( SDL_INIT_EVERYTHING ) != 0 )
		return 1;

	screen = SDL_SetVideoMode ( xDialog, yDialog, bpp, SDL_SWSURFACE );

	if ( screen == NULL )
		return -1;

	SDL_WM_SetCaption ( "Instanziare Dinamicamente Oggetti", NULL );
	

	//Dichiarazione del vettore oggetti
	vector<Ball> oggetti;
	

	//Carica le immagini
	background = SDL_LoadBMP ( "Background.bmp" );
	ball = SDL_LoadBMP ( "Ball.bmp" );
	Uint32 colorkey = SDL_MapRGB( ball->format, 0xFF, 0xFF, 0xFF );
	SDL_SetColorKey( ball, SDL_SRCCOLORKEY, colorkey );
	
	while ( true )
	{
		SDL_Delay ( frameSkip );
		if ( newobj < makeBallDelay )
			newobj += 10;
		
		SDL_PollEvent ( &evento );
		keys = SDL_GetKeyState ( NULL );

		if ( ( keys[SDLK_SPACE] == SDL_PRESSED ) && newobj == makeBallDelay )
		{
			oggetti.push_back ( Ball ( ball ) );
			newobj = 0;
		}

		if ( evento.type == SDL_QUIT ) break;

        //gestione movimento
		makeBackground();
		
		for ( int i = 0; i < oggetti.size(); i++ )
		{
			oggetti[i].makeBall ( screen );
			oggetti[i].moveBall();
			oggetti[i].ballBounce();
		}
		
		SDL_Flip ( screen );
	}
	

	freeSurfaces();
	SDL_Quit();

	return 0;
}
