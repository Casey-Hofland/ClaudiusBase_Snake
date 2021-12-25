// 2019-12-05 Teemu Laiho

#include "Game.h"
#include "RenderManager.h"

void Game::Update(float deltaTime)
{
	snake.Update(deltaTime);

	// Snake colliding on themselves.
	const auto& head = snake.Head();
	const auto& tail = snake.Tail();
	for (size_t i = 2; i < snake.BodyPartsSize(); i++)
	{
		const auto& bodyPart = snake.BodyPartAt(i);
		if (SDL_HasIntersection(&head, &bodyPart)
			&& (bodyPart.x != tail.x || bodyPart.y != tail.y))
		{
			snake = { Vector2{300.0f, 300.0f}, 10, 10 };
			break;
		}
	}

	// Snake going out of bounds.
	if (snake.GetPosition().x > width 
		|| snake.GetPosition().x < 0
		|| snake.GetPosition().y > height
		|| snake.GetPosition().y < 0)
	{
		snake = { Vector2{300.0f, 300.0f}, 10, 10 };
	}

	// Snake collide on apple
	if (SDL_HasIntersection(&snake.Head(), &apple.rect))
	{
		snake.score++;
		snake.Grow();

		apple.position = { (rand() % 125) * 10.0f, (rand() % 70) * 10.0f };
		apple.rect.x = apple.position.x;
		apple.rect.y = apple.position.y;
	}
}

void Game::Render(RenderManager& renderManager)
{
	snake.Render(renderManager.renderer);
	apple.Render(renderManager);
}

