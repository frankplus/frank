#include "SDL/SDL.h"
#include <ctime>

class ball
{
    SDL_Surface* myBall;
	enum BallDirections { TOPLEFT = 1, TOPRIGHT, BOTTOMLEFT, BOTTOMRIGHT };
	BallDirections directions;
	static const int speed = 5;
    SDL_Rect pos;
public:
    ball(int x, int y);
    ~ball() {SDL_FreeSurface(myBall);}
    inline void applyBall(SDL_Surface* screen);
    void bounceOnWall();
    void bounceOnPaddle(int Xpaddle);
    void moveBall();
};

ball::ball(int x, int y)
{
    int temp;
    
    myBall = SDL_LoadBMP("ball.bmp");
    Uint32 colorkey = SDL_MapRGB( myBall->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( myBall, SDL_SRCCOLORKEY, colorkey );
    pos.x = x;
    pos.y = y;
    srand(time(NULL));
    temp = 1 + rand() % 2;
    switch(temp)
    {
        case 1:
            directions = TOPLEFT;
            break;
        case 2:
            directions = TOPRIGHT;
            break;
    }
}

void ball::applyBall(SDL_Surface* screen)
{
    SDL_BlitSurface( myBall, NULL, screen, &pos );
}

void ball::moveBall()
{
    switch(directions)
    {
        case TOPLEFT:
            pos.x -= speed;
            pos.y -= speed;
            break;
        case TOPRIGHT:
            pos.x += speed;
            pos.y -= speed;
            break;
        case BOTTOMLEFT:
            pos.x -= speed;
            pos.y += speed;
            break;
        case BOTTOMRIGHT:
            pos.x += speed;
            pos.y += speed;
            break;
    }
}

void ball::bounceOnWall()
{
    if(pos.x<=0)
    {
        if(directions == BOTTOMLEFT)
            directions = BOTTOMRIGHT;
        else if(directions == TOPLEFT)
            directions = TOPRIGHT;
    }
            
    else if(pos.x >= 600-35 )
    {
        if(directions == BOTTOMRIGHT)
            directions = BOTTOMLEFT;
        else if(directions == TOPRIGHT)
            directions = TOPLEFT;
    }
            
    else if(pos.y<=0)
    {
        if(directions == TOPRIGHT)
            directions = BOTTOMRIGHT;
        else if(directions == TOPLEFT)
            directions = BOTTOMLEFT;
    }
            
    else if(pos.y>=600-35)
    {
        if(directions == BOTTOMRIGHT)
            directions = TOPRIGHT;
        else if(directions == BOTTOMLEFT)
            directions = TOPLEFT;
    }
}

void ball::bounceOnPaddle(int Xpaddle)
{
    if(pos.y >= 520-35 && pos.x >= Xpaddle && pos.x <= Xpaddle + 143)
    {
        if(directions == BOTTOMRIGHT)
            directions = TOPRIGHT;
        if(directions == BOTTOMLEFT)
            directions = TOPLEFT;
    }
}
