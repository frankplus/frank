/*
    author: Pham Francesco
    Alias: frankplus
    Email: binh282828@hotmail.it
*/
#include "player.h"

player::player(SDL_Rect *camera_, map *Map_, int team)
{
    camera = camera_;
    Map = Map_;

    man = NULL;
    man = new ClassSurface("gfx/players0.bmp"); //load man
    man->SetColorKey(0xFF, 0xFF, 0xFF);

    //init values
    angle = 0;
    MouseX = 0;
    MouseY = 0;

    PosOnMap.x = Map->GetPosSpawn(team).Xpos;
    PosOnMap.y = Map->GetPosSpawn(team).Ypos;
}

player::~player()
{
    delete man; //deallocate man
}

void player::SetMousePos(int x, int y)
{
    MouseX = x;
    MouseY = y;
}

void player::print(SDL_Surface *screen)
{
    //calculate angle pointing the mouse cursor
    angle = atan2((MouseX-PosOnScreen.x),(MouseY-PosOnScreen.y));
    angle *= 180/3.1416;
    angle -= 180;
    man->RotoZoom(angle,1.3); //rotate man

    //calculate position of the man
    PosOnScreen.x = PosOnMap.x-camera->x;
    PosOnScreen.y = PosOnMap.y-camera->y;

    man->move(PosOnScreen.x-man->GetWidth()/2, PosOnScreen.y-man->GetHeight()/2); //move man
    man->blit(screen); //blit to the screen
}

void player::MovePlr(int ShiftX, int ShiftY)
{
    if(!Map->CheckCollisionMap(PosOnMap.x+ShiftX, PosOnMap.y+ShiftY, radius))
    {
        PosOnMap.x += ShiftX;
        PosOnMap.y += ShiftY;
    }
}

void player::CenterCamera()
{
    camera->x = PosOnMap.x - camera->w/2;
    camera->y = PosOnMap.y - camera->h/2;
    camera->x -= shift * cos((angle*3.1416/180)-90);
    camera->y += shift * sin((angle*3.1416/180)-90);
}
