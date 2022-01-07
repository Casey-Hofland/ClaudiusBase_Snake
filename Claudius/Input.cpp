#include "Input.h"

void Input::ProcessInput()
{
    lastFrame = currentFrame;

    SDL_PumpEvents();
    int numKeys;
    auto keyboard = SDL_GetKeyboardState(&numKeys);

    currentFrame = { keyboard, keyboard + numKeys };
}

bool Input::GetKey(SDL_Scancode scancode) const noexcept
{
    return scancode < currentFrame.size()
        && currentFrame.at(scancode);
}

bool Input::GetKeyDown(SDL_Scancode scancode) const noexcept
{
    return GetKey(scancode) 
        && (scancode >= lastFrame.size()
        || !lastFrame.at(scancode));
}

bool Input::GetKeyUp(SDL_Scancode scancode) const noexcept
{
    return !GetKey(scancode) 
        && scancode < lastFrame.size()
        && lastFrame.at(scancode);
}