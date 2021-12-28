#include "Game.h"
#include <stdexcept>
#include <ctime>

Game::Game(unsigned int gridSize, unsigned int columns, unsigned int rows)
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

	std::srand(std::time(nullptr));
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
	if (snake.GetPosition().x + snake.GetSize() > GetWidth()
		|| snake.GetPosition().x < 0
		|| snake.GetPosition().y + snake.GetSize() > GetHeight()
		|| snake.GetPosition().y < 0)
	{
		snake = { Vector2{300.0f, 300.0f}, 30, 10 };
	}

	// Snake collide on apple
	if (SDL_HasIntersection(&snake.Head(), &apple.rect))
	{
		snake.score++;
		snake.Grow();

		auto [x, y] = GetRandomGridPosition();
		apple.rect.x = x;
		apple.rect.y = y;
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

std::tuple<unsigned int, unsigned int> Game::GetRandomGridIndex() const noexcept
{
	const unsigned int x = std::rand() % GetColumns();
	const unsigned int y = std::rand() % GetRows();

	return std::make_tuple(x, y);
}

std::tuple<unsigned int, unsigned int> Game::GetRandomGridPosition() const noexcept
{
	auto [column, row] = GetRandomGridIndex();
	return GridIndexToPosition(column, row);
}

std::tuple<unsigned int, unsigned int> Game::GridIndexToPosition(unsigned int column, unsigned int row) const noexcept
{
	const unsigned int gridSize = GetGridSize();
	return std::make_tuple(column * gridSize, row * gridSize);
}

std::tuple<unsigned int, unsigned int> Game::PositionToGridIndex(unsigned int x, unsigned int y) const noexcept
{
	const unsigned int gridSize = GetGridSize();
	return std::make_tuple(x / gridSize, y / gridSize);
}

unsigned int Game::GetGridSize() const noexcept
{
	return gridSize;
}

void Game::SetGridSize(unsigned int gridSize) noexcept
{
	this->gridSize = gridSize;
	snake.SetSize(gridSize);
	apple.rect.w = gridSize;
	apple.rect.h = gridSize;
}

unsigned int Game::GetColumns() const noexcept
{
	return columns;
}

void Game::SetColumns(unsigned int columns) noexcept
{
	this->columns = columns;
}

unsigned int Game::GetRows() const noexcept
{
	return rows;
}

void Game::SetRows(unsigned int rows) noexcept
{
	this->rows = rows;
}

unsigned int Game::GetWidth() const noexcept
{
	return GetGridSize() * GetColumns();
}

unsigned int Game::GetHeight() const noexcept
{
	return GetGridSize() * GetRows();
}