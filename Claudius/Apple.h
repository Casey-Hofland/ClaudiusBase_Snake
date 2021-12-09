#pragma once

#include "Transform.h"

#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable: ALL_CODE_ANALYSIS_WARNINGS)
#include "SDL.h"
#pragma warning(pop)

struct RenderManager; //<- Kinda like #include "RenderManager.h", not exactly. Can't use functions. Google forward declaration.

struct Apple
{

	Apple();
	void Render(RenderManager& renderManager);
	void Initialize(int width, int height);

	SDL_Rect rect{};
	SDL_Color color{};
	Transform trans;

	bool new_apple = false;
};