#include "SDL/SDL.h"

class paddle
{
    SDL_Surface* myPaddle;
    SDL_Rect pos;
    static const int speed = 10;
public:
    paddle(int x, int y);
    ~paddle() {SDL_FreeSurface(myPaddle);}
    inline void applyPaddle(SDL_Surface* screen);
    void movePaddle(Uint8 *keys);
    int getX() {return pos.x;}
};

paddle::paddle(int x, int y)
{
    myPaddle = SDL_LoadBMP("paddle.bmp");
    Uint32 colorkey = SDL_MapRGB( myPaddle->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( myPaddle, SDL_SRCCOLORKEY, colorkey );
    pos.x = x;
    pos.y = y;
}

void paddle::applyPaddle(SDL_Surface* screen)
{
    SDL_BlitSurface( myPaddle, NULL, screen, &pos );
}

void paddle::movePaddle(Uint8 *keys)
{
	if ( keys[SDLK_LEFT])
		pos.x -= speed;
	if ( keys[SDLK_RIGHT] && ( ( pos.x + 143 ) <= 600 ) )
		pos.x += speed;
}
