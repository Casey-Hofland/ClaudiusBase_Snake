#include "Game.h"
#include <stdexcept>

Game::Game(int gridSize, int columns, int rows)
	: gridSize{ gridSize }
	, columns{ columns }
	, rows{ rows }
{
	SDL_Init(SDL_INIT_EVERYTHING);

	// Create the window and check that it was successfully created.
	window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GetWidth(), GetHeight(), SDL_WindowFlags::SDL_WINDOW_SHOWN);
	if (window == nullptr) 
	{
		throw std::invalid_argument("Could not create window: " + std::string(SDL_GetError()) + ".\n");
	}

	// Create the renderer and check that it was successfully created.
	renderer = SDL_CreateRenderer(window, -1, SDL_RendererFlags::SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
	{
		throw std::invalid_argument("Could not create renderer: " + std::string(SDL_GetError()) + ".\n");
	}
}

Game::~Game() noexcept
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

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
			snake = { Vector2{300.0f, 300.0f}, 30, 10 };
			break;
		}
	}

	// Snake going out of bounds.
	if (snake.GetPosition().x > GetWidth()
		|| snake.GetPosition().x < 0
		|| snake.GetPosition().y > GetHeight()
		|| snake.GetPosition().y < 0)
	{
		snake = { Vector2{300.0f, 300.0f}, 30, 10 };
	}

	// Snake collide on apple
	if (SDL_HasIntersection(&snake.Head(), &apple.rect))
	{
		snake.score++;
		snake.Grow();

		apple.rect.x = (rand() % (GetWidth() / apple.rect.w)) * apple.rect.w;
		apple.rect.y = (rand() % (GetHeight() / apple.rect.h)) * apple.rect.h;
	}
}

void Game::Render() const noexcept
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	snake.Render(renderer);
	apple.Render(renderer);

	SDL_RenderPresent(renderer);
}

int Game::GetWidth() const noexcept
{
	return gridSize * columns;
}

int Game::GetHeight() const noexcept
{
	return gridSize * rows;
}