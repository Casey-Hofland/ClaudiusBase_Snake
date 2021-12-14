#pragma once

#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable: ALL_CODE_ANALYSIS_WARNINGS)
#include "SDL.h"
#pragma warning(pop)

#include <string>
#include <vector>
#include "Apple.h"
#include "Player.h"

struct RenderManager;
struct ResourceManager;

class Game
{
	Player playerOne{ Vector2{300.0f, 300.0f}, 10 };
	Apple apple{ 10, 10 };

public:
	int width{ 1250 };
	int height{ 700 };

	void Update(float deltaTime);
	void Render(RenderManager& rendererManager);
	void OnKeyDown(SDL_Keycode key);
	void OnKeyUp(SDL_Keycode key);
};
