/*
    author: Pham Francesco
    Alias: frankplus
    Email: binh282828@hotmail.it
*/
#include "surface.h"

ClassSurface::ClassSurface(std::string filename)
{
    surf = NULL;
    SDL_Surface* temp = NULL;
    //optimization of loading bmp
    temp = SDL_LoadBMP(filename.c_str());
    if(temp == NULL) PrintError(100);
    surf = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);

    //init values
    rotated = surf;
    offset.x = 0;
    offset.y = 0;
    width = surf->w;
    height = surf->h;
}

ClassSurface::~ClassSurface()
{
    SDL_FreeSurface(surf);
}

void ClassSurface::move(int x, int y)
{
    offset.x = x;
    offset.y = y;
}

void ClassSurface::move(point pnt)
{
    offset.x = pnt.x;
    offset.y = pnt.y;
}

void ClassSurface::blit(SDL_Surface* destination, SDL_Rect* clip)
{
    int ret = SDL_BlitSurface(rotated, clip, destination, &offset);
    if(ret == -1) PrintError(101);
}

void ClassSurface::MoveCenter(int DestWidth, int DestHeight)
{
    offset.x = (DestWidth-width)/2;
    offset.y = (DestHeight-height)/2;
}

void ClassSurface::SetColorKey(const Uint8 r, const Uint8 g, const Uint8 b)
{
    colorkey = SDL_MapRGB(surf->format,r,g,b);
    SDL_SetColorKey(surf, SDL_SRCCOLORKEY, colorkey);
    //if(ret == 0 || ret == -1) PrintError(101); doesn't work
}

bool ClassSurface::InBox(int x, int y) //if x and y is in the surface return true
{
    if(x>offset.x)
        if(x < offset.x+width)
            if(y>offset.y)
                if(y < offset.y+height)
                    return true;
    return false;
}

void ClassSurface::RotoZoom(double angle, double zoom, bool smooth) //rotate, zoom and smooth(ON or OFF)
{
    rotated = rotozoomSurface(surf, angle, zoom, smooth);
    width = rotated->w;
    height = rotated->h;
}
