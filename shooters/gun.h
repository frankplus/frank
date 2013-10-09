#ifndef GUN_H
#define GUN_H

#include <string>
#include "shooters.h"
#include "player.h"
#include <SDL/SDL_mixer.h>
#include "map.h"

void InitGuns(SDL_Surface *screen_, map *Map_, SDL_Rect *camera_);
void DeInitGuns();
int MoveBullets(void *data);
void PrintBullets();

struct TypeGun
{
    int quad;
    int damage;
    unsigned int delay;
    float spread;
    int clip;
    int n_clips;
    int ReloadDelay;
    float WalkingSpeed;
    float BulletSpeed;
    int money;
    int type;
    std::string name;
};

struct bullet
{
    point pos;
    float BulletSpeed;
    double angle;
};

class gun
{
    public:
        gun(TypeGun type_);
        ~gun();
        void SetPlr(player *plr_) {plr = plr_;}
        void fire();
        friend int MoveBullets(void *data);
        TypeGun type;
    protected:
    private:
        int bullets;
        int magazines;
        point pos; //if gun is not holding by a player
        player *plr; //NULL = gun not holding by a player
};

#endif // GUN_H
