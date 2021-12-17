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
#include "Time.h"
#include "Grid.h"
#include "IUpdateable.h"
#include "IRenderable.h"

class Game
{
private:
	//Player playerOne{ Vector2{300.0f, 300.0f}, 10 };
	//Apple apple{ 10, 10 };

	std::vector<IUpdateable*> updateables{};
	std::vector<IRenderable*> renderables{};

public:
	int width{ 1250 };
	int height{ 700 };
	Grid grid{};
	Time time{};
	SDL_Renderer* renderer;

	void Update(float deltaTime);
	void Render(RenderManager& rendererManager);
};
