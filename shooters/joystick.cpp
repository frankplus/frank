#include "joystick.h"

joystick::joystick()
{
    stick = NULL;

    //Check if there's any joysticks
    if(SDL_NumJoysticks() < 1) exit(13);

    //Open the joystick
    SDL_JoystickEventState(SDL_ENABLE);
    stick = SDL_JoystickOpen(1);

    //If there's a problem opening the joystick
    if(stick == NULL) exit(14);
}

joystick::~joystick()
{
    //Close the joystick
    SDL_JoystickClose(stick);
}

int joystick::Getx()
{
    return SDL_JoystickGetAxis(stick, 0)/30000;
}

int joystick::Gety()
{
    return SDL_JoystickGetAxis(stick, 1)/30000;
}
