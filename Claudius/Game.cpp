// 2019-12-05 Teemu Laiho

#include "Game.h"
#include "RenderManager.h"
#include <iostream>

Game::Game(ResourceManager& resourceManager) 
	: m_resourceManager(resourceManager)
	, width(1250)
	, height(700)
{
}

bool Game::Enter(int& width, int& height, std::string& title)
{
	width = this->width;	//1250
	height = this->height;	// 700
	title = "Snake";
	return true;
}

void Game::Update(double dt)
{
	// dt means delta time.
	// timer += dt; <- check Game.h
	// if (timer > updateInterval)
	//{
	// update snake movement
	// timer = 0.0f; or timer -= updateInterval;
	//}

	playerOne.Update(dt);

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
	if (playerOne.headPosition == apple.position)
	{
		playerOne.player_score++;
		playerOne.bodyPositions.push_front(playerOne.headPosition);

		//if (playerOne.bodyPositions.empty())
		//{
		//	playerOne.bodyPositions.push_back(playerOne.headPosition - playerOne.movement);
		//}
		//else if (playerOne.bodyPositions.size() == 1)
		//{
		//	const auto dir = playerOne.bodyPositions.back() - playerOne.headPosition;
		//	playerOne.bodyPositions.push_back(playerOne.bodyPositions.back() + dir);
		//}
		//else
		//{
		//	const auto dir = playerOne.bodyPositions.back() - playerOne.bodyPositions.at(playerOne.bodyPositions.size() - 1);
		//	playerOne.bodyPositions.push_back(playerOne.bodyPositions.back() + dir);
		//}

		apple.position = { (rand() % 125) * 10.0f, (rand() % 70) * 10.0f };
	}
}

void Game::Render(RenderManager& renderManager)
{
	playerOne.Render(renderManager);
	apple.Render(renderManager);
}

void Game::OnKeyDown(SDL_Keycode key)
{
	playerOne.OnKeyDown(key);
}

void Game::OnKeyUp(SDL_Keycode key)
{
}
