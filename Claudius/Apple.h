#pragma once

#include "Vector2.h"

#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable: ALL_CODE_ANALYSIS_WARNINGS)
#include "SDL.h"
#pragma warning(pop)

struct RenderManager; //<- Kinda like #include "RenderManager.h", not exactly. Can't use functions. Google forward declaration.

struct Apple
{
	Apple(int width, int height);
	void Render(RenderManager& renderManager);

	SDL_Rect rect{};
	SDL_Color color{ 0, SDL_MAX_UINT8, 0, SDL_MAX_SINT8 };
	Vector2 position{ 100.0f, 200.0f };
};