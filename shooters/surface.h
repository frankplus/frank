#ifndef SURFACE_H
#define SURFACE_H

#include "shooters.h"
#include <SDL/SDL.h>
#include "SDL_rotozoom.h"

class ClassSurface
{
    public:
        ClassSurface(std::string filename);
        ~ClassSurface();
        void move(int x, int y);
        void move(point pnt);
        void MoveCenter(int DestWidth, int DestHeight);
        void blit(SDL_Surface* destination, SDL_Rect* clip=NULL);
        void SetColorKey(const Uint8 r, const Uint8 g, const Uint8 b);
        bool InBox(int x, int y);
        void RotoZoom(double angle, double zoom=1, bool smooth=false);
        int GetWidth() {return width;}
        int GetHeight() {return height;}

    protected:
    private:
        SDL_Surface* surf;
        SDL_Surface* rotated;
        int width;
        int height;
        SDL_Rect offset;
        Uint32 colorkey;
};

#endif // SURFACE_H
