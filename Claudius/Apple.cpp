#pragma once

#include "Apple.h"

Apple::Apple(int x, int y, int size) noexcept
	: rect{ x, y, size, size }
{
}

void Apple::Render(SDL_Renderer* renderer) const noexcept
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &rect);
}
