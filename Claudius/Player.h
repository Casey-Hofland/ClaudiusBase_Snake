#pragma once		// #pragma once == Compile this file once.

#include <queue>
#include "Vector2.h"

#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable: ALL_CODE_ANALYSIS_WARNINGS)
#include "SDL.h"
#pragma warning(pop)

struct RenderManager;

class Player
{
public:
	Player(Vector2 position, int size);

	std::deque<Vector2> bodyPositions{};

	Vector2 headPosition{};

	SDL_Color headColor{ 0, SDL_MAX_UINT8, 0, SDL_MAX_UINT8 };
	SDL_Color bodyColor{ SDL_MAX_UINT8 , 0, 0, SDL_MAX_UINT8 };
	SDL_Rect rect{};
	void OnKeyDown(SDL_Keycode key);
	void Render(RenderManager& renderManager);				// A reference or pointer doesn't need to be #include, just a forward declare.
	void Update(double dt);

	float movement_speed{ 10.0f };

	Vector2 movement{};

	int player_score{ 0 };
};