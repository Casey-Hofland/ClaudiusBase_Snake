#include "Input.h"

bool Input::GetKey(SDL_Scancode scancode) noexcept
{
    SDL_PumpEvents();
    auto keyboard = SDL_GetKeyboardState(nullptr);

    return keyboard[scancode];
}