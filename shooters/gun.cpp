/*
    author: Pham Francesco
    Alias: frankplus
    Email: binh282828@hotmail.it
*/
#include "gun.h"

vector<bullet> FlyingBullets;
Mix_Chunk *bang = NULL;
ClassSurface *SurfBullet = NULL;
SDL_Thread *thread = NULL;
SDL_Surface *ScreenCopy = NULL;
map *Map;
SDL_Rect *cam;
SDL_sem *sem = NULL;

void SemWait()
{
    if(SDL_SemWait(sem) == -1) PrintError(400);
}

void SemPost()
{
    if(SDL_SemPost(sem) == -1) PrintError(401);
}

void InitGuns(SDL_Surface *screen_, map *Map_, SDL_Rect *camera_)
{
    ScreenCopy = screen_;
    Map = Map_;
    cam = camera_;

    bang = Mix_LoadWAV("sfx/m4a1.wav");
    if(bang == NULL) PrintError(402);
    bang->volume = 8;

    SurfBullet = new ClassSurface("gfx/particle.bmp");
    SurfBullet->SetColorKey(0xFF, 0xFF, 0xFF);

    thread = SDL_CreateThread(MoveBullets, NULL);
    //sem = SDL_CreateSemaphore(1);
}

void DeInitGuns()
{
    SDL_KillThread(thread);
    //SDL_DestroySemaphore(sem);
    delete SurfBullet;
    Mix_FreeChunk(bang);
}

int MoveBullets(void *data)
{
    unsigned int i;
    point pnt;
    for(;;)
    {
        for(i=0; i<FlyingBullets.size(); i++)
        {
            pnt.x = FlyingBullets[i].pos.x - FlyingBullets[i].BulletSpeed*10 * cos((FlyingBullets[i].angle-90)*3.1416/180);
            pnt.y = FlyingBullets[i].pos.y + FlyingBullets[i].BulletSpeed*10 * sin((FlyingBullets[i].angle-90)*3.1416/180);

            //if bullet out of screen
            if(pnt.x > SCREEN_WIDTH ||
               pnt.x < 0 ||
               pnt.y > SCREEN_HEIGHT ||
               pnt.y < 0)
            {
                FlyingBullets.erase(FlyingBullets.begin()+i);
                i--;
            }

            //if bullet collides
            else if(Map->CheckCollisionMap(pnt.x+cam->x, pnt.y+cam->y, 5, false))
            {
                FlyingBullets.erase(FlyingBullets.begin()+i);
                i--;
            }

            else
            {
                FlyingBullets[i].pos.x = pnt.x;
                FlyingBullets[i].pos.y = pnt.y;
            }
        }
        SDL_Delay(10);
    }
    return 0;
}

void PrintBullets()
{
    unsigned int i;
    point pos;
    for(i=0; i<FlyingBullets.size(); i++)
    {
        pos = FlyingBullets[i].pos;
        if(pos.x > SCREEN_WIDTH ||
           pos.x < 0 ||
           pos.y > SCREEN_HEIGHT ||
           pos.y < 0) continue;
        SurfBullet->move(pos);
        SurfBullet->blit(ScreenCopy);
    }
}

gun::gun(TypeGun type_)
{
    plr = NULL;
    type = type_;
    bullets = type.clip;
    magazines = type.n_clips;
}

gun::~gun()
{

}

void gun::fire()
{
    if(plr == NULL) PrintError(403);
    bullet MyBullet;
    MyBullet.pos = plr->GetPosOnScreen();
    MyBullet.angle = plr->GetAngle();
    MyBullet.BulletSpeed = type.BulletSpeed;
    FlyingBullets.push_back(MyBullet);
    Mix_PlayChannel(-1,bang,0);
}
