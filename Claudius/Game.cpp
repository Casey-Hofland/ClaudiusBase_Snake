// 2019-12-05 Teemu Laiho

#include "Game.h"

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

		apple.rect.x = (rand() % (width / apple.rect.w)) * apple.rect.w;
		apple.rect.y = (rand() % (height / apple.rect.h)) * apple.rect.h;
	}
}

void Game::Render(SDL_Renderer* renderer) const noexcept
{
	snake.Render(renderer);
	apple.Render(renderer);
}

