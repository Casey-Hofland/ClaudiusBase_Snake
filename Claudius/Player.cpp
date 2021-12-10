#include "Player.h"
#include <cmath>
#include "RenderManager.h"
#include <iostream>

Player::Player(Vector2 position, int size)
	: headPosition{ position }
	, rect{ 0, 0, size, size }
{
}

void Player::Render(RenderManager& renderManager)
{
	renderManager.Render(rect, headColor, headPosition);
	for (const auto& bodyPosition : bodyPositions)
	{
		renderManager.Render(rect, bodyColor, bodyPosition);
	}
}

void Player::Update(float deltaTime)
{
	if (!bodyPositions.empty())
	{
		bodyPositions.pop_back();
		bodyPositions.push_front(headPosition);
	}

	headPosition = headPosition + movement;
	//headPosition = headPosition + movement * deltaTime;

void Player::Extend()
{
	if (bodyPositions.empty())
	{
		bodyPositions.push_back(headPosition - movement);
	}
	else if (bodyPositions.size() == 1)
	{
		const auto dir = bodyPositions.back() - headPosition;
		bodyPositions.push_back(bodyPositions.back() + dir);
	}
	else
	{
		const auto dir = bodyPositions.back() - bodyPositions.at(bodyPositions.size() - 1);
		bodyPositions.push_back(bodyPositions.back() + dir);
	}
}

void Player::OnKeyDown(SDL_Keycode key)
{
	if (key == SDLK_LEFT)
	{
		movement = { -movement_speed, 0.0f };
	}
	else if (key == SDLK_RIGHT)
	{
		movement = { movement_speed, 0.0f };
	}
	else if (key == SDLK_UP)
	{
		movement = { 0.0f, -movement_speed };
	}
	else if (key == SDLK_DOWN)
	{
		movement = { 0.0f, movement_speed };
	}
}