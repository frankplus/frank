/*
    author: Pham Francesco
    Alias: frankplus
    Email: binh282828@hotmail.it
*/
#include "shooters.h"
#include <SDL/SDL.h>
#include "map.h"
#include "player.h"
#include <fstream>
#include "ttf.h"
#include "gun.h"

using namespace std;

void StartScreen();
void init();
void DeInit();
string MapScreen();

map *mappa;
SDL_Surface* screen = NULL;
SDL_Rect camera = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};

//main function
int main( int argc, char* args[] )
{
    Uint8 *keystates;
    SDL_Event event;
    bool exit = false;
    int vel;
    string name;
    bool fire;
    Uint32 start = 0;

    TypeGun TestType;
    TestType.clip = 30;
    TestType.n_clips = 4;
    TestType.BulletSpeed = 0.5;
    TestType.WalkingSpeed = 8;
    TestType.delay = 100;
    gun TestGun(TestType);

    init(); //inizializzazione
    StartScreen(); //Play screen (schermata iniziale)
    for(;;)
    {
        name = MapScreen();

        //load map
        mappa = new map(name);
        mappa->load();

        //Initialize guns
        InitGuns(screen, mappa, &camera);

        //laod player
        player plr(&camera, mappa, 0);

        //init gun player
        TestGun.SetPlr(&plr);

        //event management
        keystates = SDL_GetKeyState( NULL );
        vel = TestGun.type.WalkingSpeed;
        fire = false;
        for(;;)
        {
            if(SDL_PollEvent(&event))
            {
                switch(event.type)
                {
                    case SDL_QUIT: //when user click on X button
                        exit = true;
                        break;

                    case SDL_MOUSEMOTION: //when user move mouse
                        plr.SetMousePos(event.motion.x, event.motion.y);
                        break;

                    case SDL_MOUSEBUTTONDOWN:
                        fire = true;
                        break;

                    case SDL_MOUSEBUTTONUP:
                        fire = false;
                        break;
                }
            }

            //X button pressed
            if(exit == true) break;

            //mouse left button down
            if(fire == true)
            {
                if(SDL_GetTicks()-start > TestGun.type.delay)
                {
                    TestGun.fire();
                    start = SDL_GetTicks();
                }
            }

            //if a key is pressed
            if(keystates[SDLK_w]) plr.MovePlr(0,-vel);
            if(keystates[SDLK_s]) plr.MovePlr(0,vel);
            if(keystates[SDLK_a]) plr.MovePlr(-vel,0);
            if(keystates[SDLK_d]) plr.MovePlr(vel,0);
            if(keystates[SDLK_ESCAPE]) break; //break for and return to MapScreen()

            plr.CenterCamera();
            mappa->print(screen, camera);
            plr.print(screen);
            PrintBullets();

            if(SDL_Flip(screen) == -1) PrintError(1);

            SDL_Delay(1000/FPS);
        }//events cycle

        if(exit == true) break;
    }//MapScreen() - map cycle

    //quit
    DeInit();
    return 0;
}

void init()
{
    //Inizializzazione
    if(SDL_Init( SDL_INIT_EVERYTHING ) == -1) PrintError(2);
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
    if(screen == NULL) PrintError(3);
    SDL_WM_SetCaption("Shooters", NULL);

    //Initialize SDL_mixer
    if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 512 ) == -1) PrintError(11);
}

void DeInit()
{
    DeInitGuns();
    Mix_CloseAudio();
    SDL_FreeSurface(screen);
    SDL_Quit();
}

void StartScreen()
{
    //logo
    ClassSurface logo("gfx/bg.bmp");
    logo.blit(screen);

    ttf ttfLoaded(256);
    ttfText text(ttfLoaded.GetFont());
    text.SetColor(0,0,0);
    text.SetText("START");
    text.MoveCenter(screen->w, screen->h);
    text.BlitText(screen);
    if(SDL_Flip(screen) == -1) PrintError(4);

    SDL_Event event;
    for(;;)
    {
        if(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    exit(0);
                    break;

                case SDL_MOUSEMOTION:
                    if(text.InBox(event.motion.x, event.motion.y))
                    {
                        text.SetColor(0xFF,0,0);
                        text.SetText("START");
                        text.BlitText(screen);
                        if(SDL_Flip(screen) == -1) PrintError(5);
                    }
                    else
                    {
                        text.SetColor(0,0,0);
                        text.SetText("START");
                        text.BlitText(screen);
                        if(SDL_Flip(screen) == -1) PrintError(6);
                    }
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if(event.button.button == SDL_BUTTON_LEFT)
                        if(text.InBox(event.button.x, event.button.y))
                            return;
                    break;
            }
        }
    }
}

string MapScreen()
{
    //logo
    ClassSurface logo("gfx/bg.bmp");
    logo.blit(screen);

    ttf ttfLoaded(32);
    ttfText text(ttfLoaded.GetFont());

    text.SetColor(0,0,0);
    text.SetText("MAPS:");
    text.move((screen->w-text.GetWidth())/2,0);
    text.BlitText(screen);

    ifstream MapsNameTxt("maps/maps.txt");
    if(!MapsNameTxt || !MapsNameTxt.is_open()) PrintError(7);

    string line;
    vector<ttfText*> MapText;

    for(int i=0;;i++)
    {
        getline(MapsNameTxt,line);
        if(MapsNameTxt.eof() || MapsNameTxt.fail()) PrintError(8);
        else if(line.compare("---END---") == 0) break;
        MapText.push_back(new ttfText(ttfLoaded.GetFont()));
        MapText[i]->SetColor(0,0,0);
        MapText[i]->SetText(line);
        MapText[i]->move((screen->w-MapText[i]->GetWidth())/2, 35*(i+2));
    }
    MapsNameTxt.close();

    for(unsigned int i=0; i<MapText.size(); i++)
        MapText[i]->BlitText(screen);

    if(SDL_Flip(screen) == -1) PrintError(9);

    SDL_Event event;
    for(;;)
    {
        if(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    exit(0);
                    break;
                case SDL_MOUSEMOTION:
                    for(unsigned int i=0; i<MapText.size(); i++)
                    {
                        if(MapText[i]->InBox(event.motion.x, event.motion.y))
                            MapText[i]->SetColor(0xFF,0,0);
                        else
                            MapText[i]->SetColor(0,0,0);
                        MapText[i]->SetText(MapText[i]->GetMex());
                        MapText[i]->BlitText(screen);
                    }
                    if(SDL_Flip(screen) == -1) PrintError(10);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    for(unsigned int i=0; i<MapText.size(); i++)
                        if(MapText[i]->InBox(event.button.x, event.button.y))
                        {
                            string ret = MapText[i]->GetMex();
                            for(unsigned int i=0; i<MapText.size(); i++) delete MapText[i];
                            return(ret);
                        }
                    break;
            }
        }
    }

    return("ERROR");
}
