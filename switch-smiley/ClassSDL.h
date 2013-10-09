#ifndef CLASSSDL_H_INCLUDED
#define CLASSSDL_H_INCLUDED

#include <SDL/SDL.h>

class ClassSDL
{
private:
    SDL_Surface* screen;
    SDL_Surface* smiley;
    SDL_Surface* background;
public:
    ClassSDL();
    ~ClassSDL();
    void ApplySmiley(char* FileName);
    void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination );
};

#endif // CLASSSDL_H_INCLUDED
