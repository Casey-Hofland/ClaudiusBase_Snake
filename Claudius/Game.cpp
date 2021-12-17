// 2019-12-05 Teemu Laiho

#include "Game.h"
#include "RenderManager.h"
#include <iostream>

void Game::Update(float deltaTime)
{
	playerOne.Update(deltaTime);

	// Player colliding on theirself.
	for (int i = 0; i < playerOne.player_score; i++)
	{
		if (playerOne.headPosition == playerOne.bodyPositions[i])
		{
			playerOne = { Vector2{300.0f, 300.0f}, 10 };
		}
	}

	// Player going out of X bounds.
	if (playerOne.headPosition.x > width || playerOne.headPosition.x < 0)
	{
		playerOne = { Vector2{300.0f, 300.0f}, 10 };
	}

	// Player going out of Y bounds.
	if (playerOne.headPosition.y > height || playerOne.headPosition.y < 0)
	{
		playerOne = { Vector2{300.0f, 300.0f}, 10 };
	}

	// Player collide on apple.
	if (SDL_HasIntersection(&playerOne.headRect, &apple.rect))
	{
		playerOne.player_score++;
		playerOne.Extend();

		apple.position = { (rand() % 125) * 10.0f, (rand() % 70) * 10.0f };
		apple.rect.x = apple.position.x;
		apple.rect.y = apple.position.y;
	}
}

void Game::Render(RenderManager& renderManager)
{
	playerOne.Render(renderManager);
	apple.Render(renderManager);
}

