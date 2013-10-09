#include "ClassSDL.h"

using namespace std;

int main( int argc, char* args[] )
{
    bool quit=false;
    int i=1;
    ClassSDL stick;
    SDL_Event event;
    stick.ApplyPicture((char*)"StickMan_1.bmp");
    while(quit == false)
    {
        if(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT) quit = true;
            else if(event.type == SDL_MOUSEBUTTONDOWN)
            {
                if(++i > 4) i=1;
                switch(i)
                {
                    case 1:
                        stick.ApplyPicture((char*)"StickMan_1.bmp");
                        break;
                    case 2:
                        stick.ApplyPicture((char*)"StickMan_2.bmp");
                        break;
                    case 3:
                        stick.ApplyPicture((char*)"StickMan_3.bmp");
                        break;
                    case 4:
                        stick.ApplyPicture((char*)"StickMan_4.bmp");
                        break;
                }
            }
        }
    }
    return 0;
}
