#pragma once

#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable: ALL_CODE_ANALYSIS_WARNINGS)
#include "SDL.h"
#pragma warning(pop)

struct Apple
{
public:
	SDL_Rect rect{};
	SDL_Color color{ 0, SDL_MAX_UINT8, 0, SDL_MAX_SINT8 };

	Apple(int x, int y, int size) noexcept;
	void Render(SDL_Renderer* renderer) const noexcept;
};