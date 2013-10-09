#include "SDL/SDL.h"
#include "ball.h"
#include "paddle.h"
#include <windows.h>

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;
const int frameSkip = 10;

SDL_Surface* screen = NULL;
SDL_Surface* background = NULL;

inline void applyBackground()
{
    SDL_BlitSurface( background, NULL, screen, NULL);
}

int main(int argc, char *argv[])
{
    ball _ball(300, 485);
    paddle _paddle(250, 520);
    SDL_Event event;
    Uint8 *keys = NULL;
    
    background = SDL_LoadBMP("background.bmp");
    
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1) return 1;
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE );
    if(!screen) return 1;
    SDL_WM_SetCaption( "Pong", NULL ); //settaggio titolo in alto
    
    while(1)
    {
        SDL_Delay (frameSkip);
        SDL_PollEvent(&event);
        keys = SDL_GetKeyState(NULL);
        
        applyBackground();
        _paddle.movePaddle(keys);
        _ball.moveBall();
        _ball.bounceOnWall();
        _ball.bounceOnPaddle(_paddle.getX());
        
        _paddle.applyPaddle(screen);
        _ball.applyBall(screen);
        
        SDL_Flip(screen);
        
        if(event.type == SDL_QUIT)
        {
            MessageBox(
              NULL,
              "BYE BYE !!!!!!!!!!!!!",
              "Exit Program",
              MB_OK
            );
            break;
        }
    }
    
    SDL_FreeSurface(background);
    SDL_Quit();
    return 0;
}
