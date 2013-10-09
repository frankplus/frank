#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <SDL/SDL.h>

class joystick
{
    public:
        joystick();
        ~joystick();
        int Getx();
        int Gety();
    private:
        SDL_Joystick *stick;
};

#endif // JOYSTICK_H
