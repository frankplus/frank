#ifndef TTF_H
#define TTF_H

#include "shooters.h"
#include <string>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>

#define ttfPath "gfx/arial.ttf"

using namespace std;

class ttf
{
    public:
        ttf(int size);
        ~ttf();
        TTF_Font* GetFont() {return font;}
    protected:
    private:
        TTF_Font *font;
};

class ttfText
{
    public:
        ttfText(TTF_Font* font_);
        ~ttfText();
        void SetColor(Uint8 r, Uint8 g, Uint8 b);
        void SetText(string text);
        void move(int x, int y);
        void MoveCenter(int DestWidth, int DestHeight);
        void BlitText(SDL_Surface *dest);
        bool InBox(int x, int y);
        int GetWidth() {return width;}
        int GetHeight() {return height;}
        string GetMex();
    private:
        SDL_Color textColor;
        SDL_Rect offset;
        int width, height;
        SDL_Surface *message;
        string mex;
        TTF_Font *font;

};

#endif // TTF_H
