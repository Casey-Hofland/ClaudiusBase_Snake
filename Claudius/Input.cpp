#include "Input.h"

void Input::ProcessInput()
{
    lastFrame = currentFrame;

    SDL_PumpEvents();
    int numKeys;
    auto keyboard = SDL_GetKeyboardState(&numKeys);

    [[gsl::suppress(bounds.1, justification: "The warning is thrown by the third party SDL library.")]]
    currentFrame = { keyboard, keyboard + numKeys };
}

[[gsl::suppress(26812, justification : "The warning is thrown by the third party SDL library.")]]
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