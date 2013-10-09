//Ball.h
#include <SDL/SDL.h>
#include <ctime>

class Ball
{
public:
	Ball ( SDL_Surface * );
	~Ball ( void );
	void makeBall ( SDL_Surface * );
	void moveBall ( void );
	void ballBounce ( void );

private:
	SDL_Surface *myBall;
	SDL_Rect ballRect;
	enum ballDirections { TOPLEFT = 1, TOPRIGHT, BOTTOMLEFT, BOTTOMRIGHT };
	ballDirections Directions;
	static const int speed = 2;
	int direction;
};




Ball::Ball ( SDL_Surface *ball )
{
	myBall = ball;
	ballRect.x = 300; //al centro
	ballRect.y = 300;
	direction = 1 + rand() % 4;
	if ( direction == 1 )
		Directions = TOPLEFT;
	else if ( direction == 2 )
		Directions = TOPRIGHT;
	else if ( direction == 3 )
		Directions = BOTTOMLEFT;
	else
		Directions = BOTTOMRIGHT;
}

Ball::~Ball ( void )
{
	//Non inseriamo come al solito SDL_FreeSurface altrimenti si avrebbe un errore fatale
}

void Ball::makeBall ( SDL_Surface *screen )
{
	SDL_BlitSurface ( myBall, NULL, screen, &ballRect );
}

void Ball::moveBall ( void )
{
	if ( Directions == TOPLEFT )
	{
		ballRect.x -= speed;
		ballRect.y -= speed;
	}
	else if ( Directions == TOPRIGHT )
	{
		ballRect.x += speed;
		ballRect.y -= speed;
	}
	else if ( Directions == BOTTOMLEFT )
	{
		ballRect.x -= speed;
		ballRect.y += speed;
	}
	else
	{
		ballRect.x += speed;
		ballRect.y += speed;
	}
}

void Ball::ballBounce ( void )
{
	if ( ballRect.x <= 0 )
	{
		if ( Directions == TOPLEFT )
			Directions = TOPRIGHT;
		else
			Directions = BOTTOMRIGHT;
	}
	else if ( ballRect.x >= 600 )
	{
		if ( Directions == TOPRIGHT )
			Directions = TOPLEFT;
		else
			Directions = BOTTOMLEFT;
	}
	else if ( ballRect.y <= 0 )
	{
		if ( Directions == TOPLEFT )
			Directions = BOTTOMLEFT;
		else
			Directions = BOTTOMRIGHT;
	}
	else if ( ballRect.y >= 500 )
	{
		if ( Directions == BOTTOMLEFT )
			Directions = TOPLEFT;
		else
			Directions = TOPRIGHT;
	}
}
