#pragma once		// #pragma once == Compile this file once.

#include "Transform.h"

#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable: ALL_CODE_ANALYSIS_WARNINGS)
#include "SDL.h"
#pragma warning(pop)

struct RenderManager;

struct Player
{
	struct PlayerPart
	{
		Transform trans;
		SDL_Color color;
		SDL_Rect rect;
	};

	//Static == belongs to the class, not the object of the class.
	static const int player_size = 50;
	PlayerPart parts[player_size];
	
	Transform trans;
	SDL_Color color;
	SDL_Rect rect;
	void OnKeyDown(SDL_Keycode key);
	void Initialize();
	void Render(RenderManager& renderManager);				// A reference or pointer doesn't need to be #include, just a forward declare.
	void Update(double dt);
	void ResetPlayer();

	int size = 10;
	const float movement_speed = 10.0f;
	const float starting_x = 300.0f;
	const float starting_y = 300.0f;

	bool moving_right = false;
	bool moving_left = false;
	bool moving_up = false;
	bool moving_down = false;
	bool new_snake = false;

	float x_array_difference[player_size] = {};
	float y_array_difference[player_size] = {};

	int player_score = 0;
};