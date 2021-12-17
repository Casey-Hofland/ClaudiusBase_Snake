#include "Player.h"
#include <cmath>
#include "RenderManager.h"

Player::Player(Vector2 position, int size)
	: headPosition{ position }
	, size{ size }
	, headRect{ static_cast<int>(position.x), static_cast<int>(position.y), size, size }
{
}

void Player::Render(RenderManager& renderManager)
{
	for (const auto& bodyPosition : bodyPositions)
	{
		renderManager.Render(headRect, bodyColor, bodyPosition);
	}
	renderManager.Render(headRect, headColor, headPosition);
}

void Player::Update(float deltaTime)
{
	UpdateInput();

	if (headRect.x % size == 0
		&& headRect.y % size == 0)
	{
		if (!bodyPositions.empty())
		{
			const Vector2 newBodyPos = Vector2{ static_cast<float>(headRect.x), static_cast<float>(headRect.y) };

			if (bodyPositions.front() != newBodyPos)
			{
				bodyPositions.pop_back();
				bodyPositions.push_front(newBodyPos);
			}
		}
	}

	headPosition += movement * movement_speed * deltaTime;
	
	headRect.x = headPosition.x;
	headRect.y = headPosition.y;
}

void Player::Extend()
{
	bodyPositions.push_back(-Vector2::one() * size);
}

void Player::UpdateInput()
{
	Vector2 newMovement = Vector2::zero();

	if (Input::GetKey(SDL_Scancode::SDL_SCANCODE_LEFT))
	{
		newMovement = Vector2::left();
	}
	else if (Input::GetKey(SDL_Scancode::SDL_SCANCODE_RIGHT))
	{
		newMovement = Vector2::right();
	}
	else if (Input::GetKey(SDL_Scancode::SDL_SCANCODE_UP))
	{
		newMovement = Vector2::down();
	}
	else if (Input::GetKey(SDL_Scancode::SDL_SCANCODE_DOWN))
	{
		newMovement = Vector2::up();
	}

	// Ignore movement if it doesn't change or would go in the opposite direction.
	if (newMovement == Vector2::zero()
		|| newMovement == movement
		|| newMovement == -movement)
	{
		return;
	}

	// Apply movement and make sure the head stays on the grid in such a way that input calculated the next frame would move the head in a different direction.
	movement = newMovement;

	headPosition /= size;

	if (!bodyPositions.empty())
	{
		const Vector2 newBodyPos = Vector2{ std::roundf(headPosition.x) * size, std::roundf(headPosition.y) * size };

		if (bodyPositions.front() != newBodyPos)
		{
			bodyPositions.pop_back();
			bodyPositions.push_front(newBodyPos);
		}
	}

	headPosition.x = std::roundf(headPosition.x);
	headPosition.y = std::roundf(headPosition.y);
	headPosition *= size;
	headPosition += movement * size * 0.5f;
}