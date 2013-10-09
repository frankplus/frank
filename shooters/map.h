#ifndef MAP_H
#define MAP_H

#include "shooters.h"
#include "surface.h"
#include <SDL/SDL.h>
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

const int TILE_WIDTH = 64;
const int TILE_HEIGHT = 64;
const int ExtraMap = 8;
const int LIMITLINES = 512;
const int LIMITPOINTSPERLINE = 512;

struct spawn
{
    int team;
    int Xpos;
    int Ypos;
    bool free;
};

class map
{
    public:
        map(std::string name);
        ~map();
        void load();
        void print(SDL_Surface *screen, SDL_Rect camera);
        bool InCamera( SDL_Rect A, SDL_Rect B );
        int GetPixelWidth() {return (width)*TILE_WIDTH;}
        int GetPixelHeight() {return (height)*TILE_HEIGHT;}
        bool CheckCollisionMap(int posX, int posY, int radius, bool people=true);
        spawn GetPosSpawn(int team);
    protected:
    private:
        int TilesInX;
        int TilesInY;
        ClassSurface *TileSheet;
        SDL_Rect *clip;
        std::string MapName;
        int **TileTypes;
        int width;
        int height;
        int bgType;
        vector<vector<point> > collisions;
        vector<vector<point> > CollisionPeople;
        vector<spawn> SpawnsArr;
};

#endif // MAP_H
