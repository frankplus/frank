#include "ClassSDL.h"

using namespace std;

int main( int argc, char* args[] )
{
    bool quit=false;
    int i=1;
    ClassSDL smiley;
    SDL_Event event;
    smiley.ApplySmiley((char*)"1.bmp");
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
                        smiley.ApplySmiley((char*)"1.bmp");
                        break;
                    case 2:
                        smiley.ApplySmiley((char*)"2.bmp");
                        break;
                    case 3:
                        smiley.ApplySmiley((char*)"3.bmp");
                        break;
                    case 4:
                        smiley.ApplySmiley((char*)"4.bmp");
                        break;
                }
            }
        }
    }
    return 0;
}
