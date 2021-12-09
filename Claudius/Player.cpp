#include "Player.h"
#include <cmath>
#include "RenderManager.h"
#include <iostream>

void Player::Initialize()
{
	color = { 0,255,0,0 };
	rect = { 0, 0, size, size };
	position = { starting_x, starting_y };
	player_score = 0;

	for (int i = 0; i < player_size; i++)
	{
		parts[i].color = { 255, 0, 0, 0 };
		parts[i].rect = { 0, 0, size, size };
		parts[i].position = position;
	}
}

void Player::Render(RenderManager& renderManager)
{
	renderManager.Render(rect, color, position);

	for (int i = 0; i < player_score; i++)
	{
		renderManager.Render(parts[i].rect, parts[i].color, parts[i].position);
	}
}

void Player::Update(double dt)
{
	x_array_difference[0] = position.x - parts[0].position.x;
	y_array_difference[0] = position.y - parts[0].position.y;

	for (int i = 1; i < (player_size - 1); i++)
	{
			x_array_difference[i] = parts[i].position.x - parts[i + 1].position.x;
			y_array_difference[i] = parts[i].position.y - parts[i + 1].position.y;
	}

	if (moving_left == true)
	{
		position.x -= movement_speed;
	}
	else if (moving_right == true)
	{
		position.x += movement_speed;
	}
	else if (moving_up == true)
	{
		position.y -= movement_speed;
	}
	else if (moving_down == true)
	{
		position.y += movement_speed;
	}

	parts[0].position = parts[0].position + Vector2{ x_array_difference[0], y_array_difference[0] };

	for (int i = 1; i < player_size; i++)
	{
		parts[i].position = parts[i].position + Vector2{ x_array_difference[i - 1], y_array_difference[i - 1] };
	}
}

void Player::OnKeyDown(SDL_Keycode key)
{
	if (key == SDLK_LEFT)
	{
		moving_left = true;
		moving_right = false;
		moving_up = false;
		moving_down = false;
	}
	else if (key == SDLK_RIGHT)
	{
		moving_left = false;
		moving_right = true;
		moving_up = false;
		moving_down = false;
	}
	else if (key == SDLK_UP)
	{
		moving_left = false;
		moving_right = false;
		moving_up = true;
		moving_down = false;
	}
	else if (key == SDLK_DOWN)
	{
		moving_left = false;
		moving_right = false;
		moving_up = false;
		moving_down = true;
	}
}

void Player::ResetPlayer()
{
	player_score = 0;
	moving_right = false;
	moving_left = false;
	moving_up = false;
	moving_down = false;

	position = { starting_x, starting_y };
}