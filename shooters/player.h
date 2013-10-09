#ifndef PLAYER_H
#define PLAYER_H

#include "shooters.h"
#include "surface.h"
#include <cmath>
#include "map.h"

const int radius = 15;
const int shift = 50;

class player
{
    public:
        player(SDL_Rect *camera_, map *Map_, int team);
        ~player();
        void SetMousePos(int x, int y);
        void print(SDL_Surface *screen);
        void MovePlr(int ShiftX, int ShiftY);
        void CenterCamera();
        double GetAngle() {return angle;}
        point GetPosOnScreen() {return PosOnScreen;}
    protected:
    private:
        SDL_Rect *camera;
        map *Map;
        ClassSurface* man;
        double angle;
        int MouseX;
        int MouseY;
        point PosOnScreen;
        point PosOnMap;
};

#endif // PLAYER_H
