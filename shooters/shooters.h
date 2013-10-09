#ifndef ERROR_H_INCLUDED
#define ERROR_H_INCLUDED

#include <windows.h>
#include <SDL/SDL_error.h>
#include <string>
#include <cmath>
#include <SDL/SDL.h>

const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 544;
const int SCREEN_BPP = 32;
const int FPS = 40;
const int zoom = 2;

struct point
{
    int x,y;
};

void PrintError(int num);
bool CheckCollision(point A, point B, point C, int radius);
float distance(point A, point B);
bool inside(point P, point A, point B);
void SemWait();
void SemPost();

#endif // ERROR_H_INCLUDED
