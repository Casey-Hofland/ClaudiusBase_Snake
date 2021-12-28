#pragma once

#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable: ALL_CODE_ANALYSIS_WARNINGS)
#include "SDL.h"
#pragma warning(pop)

#include <string>
#include <vector>
#include "Apple.h"
#include "Snake.h"
#include "Time.h"

class Game
{
private:
	Snake snake{ Vector2{300.0f, 300.0f}, 10, 10 };
	Apple apple{ 120, 300, 10 };

public:
	int width{ 1250 };
	int height{ 700 };

	void Update(float deltaTime);
	void Render(SDL_Renderer* renderer) const noexcept;
};
