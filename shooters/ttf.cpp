/*
    author: Pham Francesco
    Alias: frankplus
    Email: binh282828@hotmail.it
*/
#include "ttf.h"

using namespace std;

ttf::ttf(int size)
{
    font = NULL;
    if(TTF_Init() == -1) PrintError(300);
    font = TTF_OpenFont(ttfPath, size);
    if(font == NULL) PrintError(301);
}

ttf::~ttf()
{
    TTF_CloseFont(font);
    TTF_Quit();
}

ttfText::ttfText(TTF_Font* font_)
{
    if(font_ == NULL) PrintError(302);
    else font = font_;
    message = NULL;
    textColor.r = textColor.g = textColor.b = 0;
}

ttfText::~ttfText()
{
    SDL_FreeSurface(message);
}

void ttfText::SetColor(Uint8 r, Uint8 g, Uint8 b)
{
    textColor.r = r;
    textColor.g = g;
    textColor.b = b;
}

void ttfText::BlitText(SDL_Surface *dest)
{
    SDL_UnlockSurface(message);
    if(message == NULL) PrintError(304);
    int ret = SDL_BlitSurface(message, NULL, dest, &offset);
    if(ret == -1) PrintError(305);
}

void ttfText::SetText(string text)
{
    message = TTF_RenderText_Solid(font, text.c_str(), textColor);
    if(message == NULL) PrintError(307);
    mex = text;
    width = message->w;
    height = message->h;
}

void ttfText::move(int x, int y)
{
    offset.x = x;
    offset.y = y;
}


void ttfText::MoveCenter(int DestWidth, int DestHeight)
{
    offset.x = (DestWidth-width)/2;
    offset.y = (DestHeight-height)/2;
}

bool ttfText::InBox(int x, int y) //if x and y is in the surface return true
{
    if(x>offset.x)
        if(x < offset.x+width)
            if(y>offset.y)
                if(y < offset.y+height)
                    return true;
    return false;
}

string ttfText::GetMex()
{
    if(mex.size() == 0) PrintError(308);
    return mex;
}
